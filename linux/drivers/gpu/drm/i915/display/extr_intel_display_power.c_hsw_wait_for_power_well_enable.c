#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i915_power_well_regs {int /*<<< orphan*/  driver; } ;
struct i915_power_well {TYPE_2__* desc; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_3__ {int idx; int /*<<< orphan*/  is_tc_tbt; struct i915_power_well_regs* regs; } ;
struct TYPE_4__ {TYPE_1__ hsw; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HSW_PWR_WELL_CTL_STATE (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ intel_de_wait_for_set (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hsw_wait_for_power_well_enable(struct drm_i915_private *dev_priv,
					   struct i915_power_well *power_well)
{
	const struct i915_power_well_regs *regs = power_well->desc->hsw.regs;
	int pw_idx = power_well->desc->hsw.idx;

	/* Timeout for PW1:10 us, AUX:not specified, other PWs:20 us. */
	if (intel_de_wait_for_set(dev_priv, regs->driver,
				  HSW_PWR_WELL_CTL_STATE(pw_idx), 1)) {
		DRM_DEBUG_KMS("%s power well enable timeout\n",
			      power_well->desc->name);

		/* An AUX timeout is expected if the TBT DP tunnel is down. */
		WARN_ON(!power_well->desc->hsw.is_tc_tbt);
	}
}