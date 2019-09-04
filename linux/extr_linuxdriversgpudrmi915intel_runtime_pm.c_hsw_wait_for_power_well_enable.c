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
struct i915_power_well {int id; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum i915_power_well_id { ____Placeholder_i915_power_well_id } i915_power_well_id ;

/* Variables and functions */
 int /*<<< orphan*/  HSW_PWR_WELL_CTL_DRIVER (int) ; 
 int /*<<< orphan*/  HSW_PWR_WELL_CTL_STATE (int) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_wait_for_register (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hsw_wait_for_power_well_enable(struct drm_i915_private *dev_priv,
					   struct i915_power_well *power_well)
{
	enum i915_power_well_id id = power_well->id;

	/* Timeout for PW1:10 us, AUX:not specified, other PWs:20 us. */
	WARN_ON(intel_wait_for_register(dev_priv,
					HSW_PWR_WELL_CTL_DRIVER(id),
					HSW_PWR_WELL_CTL_STATE(id),
					HSW_PWR_WELL_CTL_STATE(id),
					1));
}