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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ low_vswing; } ;
struct TYPE_4__ {TYPE_1__ edp; } ;
struct drm_i915_private {TYPE_2__ vbt; } ;
struct cnl_ddi_buf_trans {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct cnl_ddi_buf_trans const*) ; 
 int /*<<< orphan*/  CNL_PORT_COMP_DW3 ; 
 scalar_t__ I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MISSING_CASE (scalar_t__) ; 
 scalar_t__ VOLTAGE_INFO_0_85V ; 
 scalar_t__ VOLTAGE_INFO_0_95V ; 
 scalar_t__ VOLTAGE_INFO_1_05V ; 
 scalar_t__ VOLTAGE_INFO_MASK ; 
 struct cnl_ddi_buf_trans const* cnl_ddi_translations_edp_0_85V ; 
 struct cnl_ddi_buf_trans const* cnl_ddi_translations_edp_0_95V ; 
 struct cnl_ddi_buf_trans const* cnl_ddi_translations_edp_1_05V ; 
 struct cnl_ddi_buf_trans const* cnl_get_buf_trans_dp (struct drm_i915_private*,int*) ; 

__attribute__((used)) static const struct cnl_ddi_buf_trans *
cnl_get_buf_trans_edp(struct drm_i915_private *dev_priv, int *n_entries)
{
	u32 voltage = I915_READ(CNL_PORT_COMP_DW3) & VOLTAGE_INFO_MASK;

	if (dev_priv->vbt.edp.low_vswing) {
		if (voltage == VOLTAGE_INFO_0_85V) {
			*n_entries = ARRAY_SIZE(cnl_ddi_translations_edp_0_85V);
			return cnl_ddi_translations_edp_0_85V;
		} else if (voltage == VOLTAGE_INFO_0_95V) {
			*n_entries = ARRAY_SIZE(cnl_ddi_translations_edp_0_95V);
			return cnl_ddi_translations_edp_0_95V;
		} else if (voltage == VOLTAGE_INFO_1_05V) {
			*n_entries = ARRAY_SIZE(cnl_ddi_translations_edp_1_05V);
			return cnl_ddi_translations_edp_1_05V;
		} else {
			*n_entries = 1; /* shut up gcc */
			MISSING_CASE(voltage);
		}
		return NULL;
	} else {
		return cnl_get_buf_trans_dp(dev_priv, n_entries);
	}
}