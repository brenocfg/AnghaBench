#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct drm_printer {int dummy; } ;
struct drm_i915_private {int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DRM_I915_DEBUG ; 
 int /*<<< orphan*/  CONFIG_DRM_I915_DEBUG_GEM ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int DRM_UT_DRIVER ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int drm_debug ; 
 struct drm_printer drm_debug_printer (char*) ; 
 int /*<<< orphan*/  intel_device_info_dump (int /*<<< orphan*/ *,struct drm_printer*) ; 
 int /*<<< orphan*/  intel_device_info_dump_runtime (int /*<<< orphan*/ *,struct drm_printer*) ; 

__attribute__((used)) static void i915_welcome_messages(struct drm_i915_private *dev_priv)
{
	if (drm_debug & DRM_UT_DRIVER) {
		struct drm_printer p = drm_debug_printer("i915 device info:");

		intel_device_info_dump(&dev_priv->info, &p);
		intel_device_info_dump_runtime(&dev_priv->info, &p);
	}

	if (IS_ENABLED(CONFIG_DRM_I915_DEBUG))
		DRM_INFO("DRM_I915_DEBUG enabled\n");
	if (IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM))
		DRM_INFO("DRM_I915_DEBUG_GEM enabled\n");
}