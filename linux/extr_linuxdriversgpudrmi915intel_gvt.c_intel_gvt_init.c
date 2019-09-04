#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_i915_private {int dummy; } ;
struct TYPE_2__ {scalar_t__ enable_gvt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EIO ; 
 int ENODEV ; 
 scalar_t__ USES_GUC_SUBMISSION (struct drm_i915_private*) ; 
 scalar_t__ i915_inject_load_failure () ; 
 TYPE_1__ i915_modparams ; 
 int intel_gvt_init_device (struct drm_i915_private*) ; 
 int intel_gvt_init_host () ; 

int intel_gvt_init(struct drm_i915_private *dev_priv)
{
	int ret;

	if (i915_inject_load_failure())
		return -ENODEV;

	if (!i915_modparams.enable_gvt) {
		DRM_DEBUG_DRIVER("GVT-g is disabled by kernel params\n");
		return 0;
	}

	if (USES_GUC_SUBMISSION(dev_priv)) {
		DRM_ERROR("i915 GVT-g loading failed due to Graphics virtualization is not yet supported with GuC submission\n");
		return -EIO;
	}

	/*
	 * We're not in host or fail to find a MPT module, disable GVT-g
	 */
	ret = intel_gvt_init_host();
	if (ret) {
		DRM_DEBUG_DRIVER("Not in host or MPT modules not found\n");
		goto bail;
	}

	ret = intel_gvt_init_device(dev_priv);
	if (ret) {
		DRM_DEBUG_DRIVER("Fail to init GVT device\n");
		goto bail;
	}

	return 0;

bail:
	i915_modparams.enable_gvt = 0;
	return 0;
}