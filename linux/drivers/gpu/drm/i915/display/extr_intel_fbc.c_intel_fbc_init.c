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
struct intel_fbc {int enabled; int active; char* no_fbc_reason; int /*<<< orphan*/  lock; int /*<<< orphan*/  underrun_work; } ;
struct drm_i915_private {struct intel_fbc fbc; } ;
struct TYPE_6__ {int /*<<< orphan*/  enable_fbc; } ;
struct TYPE_4__ {int has_fbc; } ;
struct TYPE_5__ {TYPE_1__ display; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FBC_CONTROL ; 
 int FBC_CTL_INTERVAL_SHIFT ; 
 int /*<<< orphan*/  HAS_FBC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_GM45 (struct drm_i915_private*) ; 
 TYPE_3__ i915_modparams ; 
 int /*<<< orphan*/  intel_fbc_hw_deactivate (struct drm_i915_private*) ; 
 scalar_t__ intel_fbc_hw_is_active (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_fbc_underrun_work_fn ; 
 int /*<<< orphan*/  intel_sanitize_fbc_option (struct drm_i915_private*) ; 
 TYPE_2__* mkwrite_device_info (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ need_fbc_vtd_wa (struct drm_i915_private*) ; 

void intel_fbc_init(struct drm_i915_private *dev_priv)
{
	struct intel_fbc *fbc = &dev_priv->fbc;

	INIT_WORK(&fbc->underrun_work, intel_fbc_underrun_work_fn);
	mutex_init(&fbc->lock);
	fbc->enabled = false;
	fbc->active = false;

	if (need_fbc_vtd_wa(dev_priv))
		mkwrite_device_info(dev_priv)->display.has_fbc = false;

	i915_modparams.enable_fbc = intel_sanitize_fbc_option(dev_priv);
	DRM_DEBUG_KMS("Sanitized enable_fbc value: %d\n",
		      i915_modparams.enable_fbc);

	if (!HAS_FBC(dev_priv)) {
		fbc->no_fbc_reason = "unsupported by this chipset";
		return;
	}

	/* This value was pulled out of someone's hat */
	if (INTEL_GEN(dev_priv) <= 4 && !IS_GM45(dev_priv))
		I915_WRITE(FBC_CONTROL, 500 << FBC_CTL_INTERVAL_SHIFT);

	/* We still don't have any sort of hardware state readout for FBC, so
	 * deactivate it in case the BIOS activated it to make sure software
	 * matches the hardware state. */
	if (intel_fbc_hw_is_active(dev_priv))
		intel_fbc_hw_deactivate(dev_priv);
}