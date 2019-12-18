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
struct intel_device_info {int has_rc6; int has_rps; scalar_t__ has_rc6p; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 int /*<<< orphan*/  bxt_check_bios_rc6_setup (struct drm_i915_private*) ; 
 scalar_t__ intel_vgpu_active (struct drm_i915_private*) ; 
 struct intel_device_info* mkwrite_device_info (struct drm_i915_private*) ; 

__attribute__((used)) static bool sanitize_rc6(struct drm_i915_private *i915)
{
	struct intel_device_info *info = mkwrite_device_info(i915);

	/* Powersaving is controlled by the host when inside a VM */
	if (intel_vgpu_active(i915)) {
		info->has_rc6 = 0;
		info->has_rps = false;
	}

	if (info->has_rc6 &&
	    IS_GEN9_LP(i915) && !bxt_check_bios_rc6_setup(i915)) {
		DRM_INFO("RC6 disabled by BIOS\n");
		info->has_rc6 = 0;
	}

	/*
	 * We assume that we do not have any deep rc6 levels if we don't have
	 * have the previous rc6 level supported, i.e. we use HAS_RC6()
	 * as the initial coarse check for rc6 in general, moving on to
	 * progressively finer/deeper levels.
	 */
	if (!info->has_rc6 && info->has_rc6p)
		info->has_rc6p = 0;

	return info->has_rc6;
}