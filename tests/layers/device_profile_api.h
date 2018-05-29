/*
 *
 * Copyright (c) 2016-2017 Valve Corporation
 * Copyright (c) 2016-2017 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: Arda Coskunses <arda@lunarg.com>
 *
 */

#ifndef __VK_DEVICE_PROFILE_API_H__
#define __VK_DEVICE_PROFILE_API_H__

#include <unordered_map>
#include "vulkan/vulkan.h"
#include "vk_layer_config.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

// Device Profile Layer

#define DEVICE_PROFILE_API_EXTENSION_NAME "VK_LUNARG_DEVICE_PROFILE"

struct PairHash {
    size_t operator()(const std::pair<int, int> pair) const { return std::hash<int>()(pair.first) + std::hash<int>()(pair.second); }
};

struct PhysicalDeviceData {
    VkInstance instance;
    VkPhysicalDeviceProperties phy_device_props;
    std::unordered_map<VkFormat, VkFormatProperties, std::hash<int> > format_properties_map;
    std::unordered_map<std::pair<VkFormat, VkImageTiling>, std::pair<VkResult, VkImageFormatProperties>, PairHash>
        image_format_properties_map;
};

struct DeviceData {
    std::unordered_map<VkImage, VkMemoryRequirements> memory_requirements_map;
};

struct InstanceLayerData {
    VkInstance instance;

    VkLayerInstanceDispatchTable *instance_dispatch_table;
};

struct DeviceLayerData {
    VkLayerDispatchTable *device_dispatch_table;
};

static std::unordered_map<VkPhysicalDevice, struct PhysicalDeviceData> physical_device_data;
static std::unordered_map<VkDevice, struct DeviceData> device_data;

// API functions
typedef void(VKAPI_PTR *PFN_vkGetOriginalPhysicalDeviceLimitsEXT)(VkPhysicalDevice physicalDevice,
                                                                  const VkPhysicalDeviceLimits *limits);
typedef void(VKAPI_PTR *PFN_vkSetPhysicalDeviceLimitsEXT)(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceLimits *newLimits);
typedef void(VKAPI_PTR *PFN_vkGetOriginalPhysicalDeviceFormatPropertiesEXT)(VkPhysicalDevice physicalDevice, VkFormat format,
                                                                            VkFormatProperties *properties);
typedef void(VKAPI_PTR *PFN_vkSetPhysicalDeviceFormatPropertiesEXT)(VkPhysicalDevice physicalDevice, VkFormat format,
                                                                    const VkFormatProperties newProperties);
typedef VkResult(VKAPI_PTR *PFN_vkGetOriginalPhysicalDeviceImageFormatPropertiesEXT)(
    VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage,
    VkImageCreateFlags flags, VkImageFormatProperties *pImageFormatProperties);
typedef void(VKAPI_PTR *PFN_vkSetPhysicalDeviceImageFormatPropertiesEXT)(VkPhysicalDevice physicalDevice, VkFormat format,
                                                                         VkImageTiling tiling, const VkResult new_result,
                                                                         const VkImageFormatProperties new_properties);
typedef void(VKAPI_PTR *PFN_vkGetOriginalImageMemoryRequirementsEXT)(VkDevice device, VkImage image,
                                                                     VkMemoryRequirements *pMemoryRequirements);
typedef void(VKAPI_PTR *PFN_vkSetImageMemoryRequirementsEXT)(VkDevice device, VkImage image,
                                                             const VkMemoryRequirements new_requirements);

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  // __VK_DEVICE_PROFILE_API_H__
