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
typedef  int /*<<< orphan*/  u32 ;
struct i915_power_well {TYPE_2__* desc; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum aux_ch { ____Placeholder_aux_ch } aux_ch ;
struct TYPE_3__ {scalar_t__ is_tc_tbt; } ;
struct TYPE_4__ {TYPE_1__ hsw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_AUX_CH_CTL (int) ; 
 int /*<<< orphan*/  DP_AUX_CH_CTL_TBT_IO ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsw_power_well_enable (struct drm_i915_private*,struct i915_power_well*) ; 
 int icl_tc_phy_aux_ch (struct drm_i915_private*,struct i915_power_well*) ; 
 int /*<<< orphan*/  icl_tc_port_assert_ref_held (struct drm_i915_private*,struct i915_power_well*) ; 

__attribute__((used)) static void
icl_tc_phy_aux_power_well_enable(struct drm_i915_private *dev_priv,
				 struct i915_power_well *power_well)
{
	enum aux_ch aux_ch = icl_tc_phy_aux_ch(dev_priv, power_well);
	u32 val;

	icl_tc_port_assert_ref_held(dev_priv, power_well);

	val = I915_READ(DP_AUX_CH_CTL(aux_ch));
	val &= ~DP_AUX_CH_CTL_TBT_IO;
	if (power_well->desc->hsw.is_tc_tbt)
		val |= DP_AUX_CH_CTL_TBT_IO;
	I915_WRITE(DP_AUX_CH_CTL(aux_ch), val);

	hsw_power_well_enable(dev_priv, power_well);
}