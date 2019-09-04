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
struct TYPE_2__ {int /*<<< orphan*/  enable_ppgtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ i915_modparams ; 
 int /*<<< orphan*/  intel_gvt_sanitize_options (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_sanitize_enable_ppgtt (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_sanitize_options(struct drm_i915_private *dev_priv)
{
	/*
	 * i915.enable_ppgtt is read-only, so do an early pass to validate the
	 * user's requested state against the hardware/driver capabilities.  We
	 * do this now so that we can print out any log messages once rather
	 * than every time we check intel_enable_ppgtt().
	 */
	i915_modparams.enable_ppgtt =
		intel_sanitize_enable_ppgtt(dev_priv,
					    i915_modparams.enable_ppgtt);
	DRM_DEBUG_DRIVER("ppgtt mode: %i\n", i915_modparams.enable_ppgtt);

	intel_gvt_sanitize_options(dev_priv);
}