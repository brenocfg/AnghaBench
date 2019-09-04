#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_6__ {int has_full_ppgtt; int has_full_48bit_ppgtt; int /*<<< orphan*/  has_aliasing_ppgtt; } ;
struct drm_i915_private {TYPE_2__ drm; TYPE_3__ info; } ;
struct TYPE_4__ {int revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 scalar_t__ HAS_LOGICAL_RING_CONTEXTS (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN6 (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 scalar_t__ intel_vgpu_active (struct drm_i915_private*) ; 
 int intel_vgpu_has_full_48bit_ppgtt (struct drm_i915_private*) ; 
 scalar_t__ intel_vtd_active () ; 

int intel_sanitize_enable_ppgtt(struct drm_i915_private *dev_priv,
			       	int enable_ppgtt)
{
	bool has_full_ppgtt;
	bool has_full_48bit_ppgtt;

	if (!dev_priv->info.has_aliasing_ppgtt)
		return 0;

	has_full_ppgtt = dev_priv->info.has_full_ppgtt;
	has_full_48bit_ppgtt = dev_priv->info.has_full_48bit_ppgtt;

	if (intel_vgpu_active(dev_priv)) {
		/* GVT-g has no support for 32bit ppgtt */
		has_full_ppgtt = false;
		has_full_48bit_ppgtt = intel_vgpu_has_full_48bit_ppgtt(dev_priv);
	}

	/*
	 * We don't allow disabling PPGTT for gen9+ as it's a requirement for
	 * execlists, the sole mechanism available to submit work.
	 */
	if (enable_ppgtt == 0 && INTEL_GEN(dev_priv) < 9)
		return 0;

	if (enable_ppgtt == 1)
		return 1;

	if (enable_ppgtt == 2 && has_full_ppgtt)
		return 2;

	if (enable_ppgtt == 3 && has_full_48bit_ppgtt)
		return 3;

	/* Disable ppgtt on SNB if VT-d is on. */
	if (IS_GEN6(dev_priv) && intel_vtd_active()) {
		DRM_INFO("Disabling PPGTT because VT-d is on\n");
		return 0;
	}

	/* Early VLV doesn't have this */
	if (IS_VALLEYVIEW(dev_priv) && dev_priv->drm.pdev->revision < 0xb) {
		DRM_DEBUG_DRIVER("disabling PPGTT on pre-B3 step VLV\n");
		return 0;
	}

	if (HAS_LOGICAL_RING_CONTEXTS(dev_priv)) {
		if (has_full_48bit_ppgtt)
			return 3;

		if (has_full_ppgtt)
			return 2;
	}

	return 1;
}