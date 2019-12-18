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
struct intel_fbc {char* no_fbc_reason; scalar_t__ underrun_detected; } ;
struct drm_i915_private {struct intel_fbc fbc; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable_fbc; } ;

/* Variables and functions */
 TYPE_1__ i915_modparams ; 
 scalar_t__ intel_vgpu_active (struct drm_i915_private*) ; 

__attribute__((used)) static bool intel_fbc_can_enable(struct drm_i915_private *dev_priv)
{
	struct intel_fbc *fbc = &dev_priv->fbc;

	if (intel_vgpu_active(dev_priv)) {
		fbc->no_fbc_reason = "VGPU is active";
		return false;
	}

	if (!i915_modparams.enable_fbc) {
		fbc->no_fbc_reason = "disabled per module param or by default";
		return false;
	}

	if (fbc->underrun_detected) {
		fbc->no_fbc_reason = "underrun detected";
		return false;
	}

	return true;
}