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
typedef  int u32 ;
struct icl_combo_phy_ddi_buf_trans {int dummy; } ;
struct TYPE_3__ {scalar_t__ low_vswing; } ;
struct TYPE_4__ {TYPE_1__ edp; } ;
struct drm_i915_private {TYPE_2__ vbt; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int ARRAY_SIZE (struct icl_combo_phy_ddi_buf_trans const*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICL_PORT_COMP_DW3 (int) ; 
 int INTEL_OUTPUT_EDP ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
#define  VOLTAGE_INFO_0_85V 130 
#define  VOLTAGE_INFO_0_95V 129 
#define  VOLTAGE_INFO_1_05V 128 
 int VOLTAGE_INFO_MASK ; 
 struct icl_combo_phy_ddi_buf_trans const* icl_combo_phy_ddi_translations_dp_hdmi_0_85V ; 
 struct icl_combo_phy_ddi_buf_trans const* icl_combo_phy_ddi_translations_dp_hdmi_0_95V ; 
 struct icl_combo_phy_ddi_buf_trans const* icl_combo_phy_ddi_translations_dp_hdmi_1_05V ; 
 struct icl_combo_phy_ddi_buf_trans const* icl_combo_phy_ddi_translations_edp_0_85V ; 
 struct icl_combo_phy_ddi_buf_trans const* icl_combo_phy_ddi_translations_edp_0_95V ; 
 struct icl_combo_phy_ddi_buf_trans const* icl_combo_phy_ddi_translations_edp_1_05V ; 

__attribute__((used)) static const struct icl_combo_phy_ddi_buf_trans *
icl_get_combo_buf_trans(struct drm_i915_private *dev_priv, enum port port,
			int type, int *n_entries)
{
	u32 voltage = I915_READ(ICL_PORT_COMP_DW3(port)) & VOLTAGE_INFO_MASK;

	if (type == INTEL_OUTPUT_EDP && dev_priv->vbt.edp.low_vswing) {
		switch (voltage) {
		case VOLTAGE_INFO_0_85V:
			*n_entries = ARRAY_SIZE(icl_combo_phy_ddi_translations_edp_0_85V);
			return icl_combo_phy_ddi_translations_edp_0_85V;
		case VOLTAGE_INFO_0_95V:
			*n_entries = ARRAY_SIZE(icl_combo_phy_ddi_translations_edp_0_95V);
			return icl_combo_phy_ddi_translations_edp_0_95V;
		case VOLTAGE_INFO_1_05V:
			*n_entries = ARRAY_SIZE(icl_combo_phy_ddi_translations_edp_1_05V);
			return icl_combo_phy_ddi_translations_edp_1_05V;
		default:
			MISSING_CASE(voltage);
			return NULL;
		}
	} else {
		switch (voltage) {
		case VOLTAGE_INFO_0_85V:
			*n_entries = ARRAY_SIZE(icl_combo_phy_ddi_translations_dp_hdmi_0_85V);
			return icl_combo_phy_ddi_translations_dp_hdmi_0_85V;
		case VOLTAGE_INFO_0_95V:
			*n_entries = ARRAY_SIZE(icl_combo_phy_ddi_translations_dp_hdmi_0_95V);
			return icl_combo_phy_ddi_translations_dp_hdmi_0_95V;
		case VOLTAGE_INFO_1_05V:
			*n_entries = ARRAY_SIZE(icl_combo_phy_ddi_translations_dp_hdmi_1_05V);
			return icl_combo_phy_ddi_translations_dp_hdmi_1_05V;
		default:
			MISSING_CASE(voltage);
			return NULL;
		}
	}
}