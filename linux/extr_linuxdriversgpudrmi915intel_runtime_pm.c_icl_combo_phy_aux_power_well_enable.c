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
typedef  int u32 ;
struct i915_power_well {int id; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;
typedef  enum i915_power_well_id { ____Placeholder_i915_power_well_id } i915_power_well_id ;

/* Variables and functions */
 int /*<<< orphan*/  HSW_PWR_WELL_CTL_DRIVER (int) ; 
 int HSW_PWR_WELL_CTL_REQ (int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int ICL_AUX_PW_TO_PORT (int) ; 
 int ICL_LANE_ENABLE_AUX ; 
 int /*<<< orphan*/  ICL_PORT_CL_DW12 (int) ; 
 int /*<<< orphan*/  hsw_wait_for_power_well_enable (struct drm_i915_private*,struct i915_power_well*) ; 

__attribute__((used)) static void
icl_combo_phy_aux_power_well_enable(struct drm_i915_private *dev_priv,
				    struct i915_power_well *power_well)
{
	enum i915_power_well_id id = power_well->id;
	enum port port = ICL_AUX_PW_TO_PORT(id);
	u32 val;

	val = I915_READ(HSW_PWR_WELL_CTL_DRIVER(id));
	I915_WRITE(HSW_PWR_WELL_CTL_DRIVER(id), val | HSW_PWR_WELL_CTL_REQ(id));

	val = I915_READ(ICL_PORT_CL_DW12(port));
	I915_WRITE(ICL_PORT_CL_DW12(port), val | ICL_LANE_ENABLE_AUX);

	hsw_wait_for_power_well_enable(dev_priv, power_well);
}