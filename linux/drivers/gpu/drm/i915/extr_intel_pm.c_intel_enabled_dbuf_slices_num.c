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
typedef  int u8 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBUF_CTL_S2 ; 
 int DBUF_POWER_STATE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 

__attribute__((used)) static u8 intel_enabled_dbuf_slices_num(struct drm_i915_private *dev_priv)
{
	u8 enabled_slices;

	/* Slice 1 will always be enabled */
	enabled_slices = 1;

	/* Gen prior to GEN11 have only one DBuf slice */
	if (INTEL_GEN(dev_priv) < 11)
		return enabled_slices;

	/*
	 * FIXME: for now we'll only ever use 1 slice; pretend that we have
	 * only that 1 slice enabled until we have a proper way for on-demand
	 * toggling of the second slice.
	 */
	if (0 && I915_READ(DBUF_CTL_S2) & DBUF_POWER_STATE)
		enabled_slices++;

	return enabled_slices;
}