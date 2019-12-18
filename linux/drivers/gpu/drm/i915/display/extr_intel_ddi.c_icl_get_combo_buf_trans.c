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
struct TYPE_3__ {scalar_t__ low_vswing; } ;
struct TYPE_4__ {TYPE_1__ edp; } ;
struct drm_i915_private {TYPE_2__ vbt; } ;
struct cnl_ddi_buf_trans {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct cnl_ddi_buf_trans const*) ; 
 int INTEL_OUTPUT_EDP ; 
 int INTEL_OUTPUT_HDMI ; 
 struct cnl_ddi_buf_trans const* icl_combo_phy_ddi_translations_dp_hbr2 ; 
 struct cnl_ddi_buf_trans const* icl_combo_phy_ddi_translations_edp_hbr2 ; 
 struct cnl_ddi_buf_trans const* icl_combo_phy_ddi_translations_edp_hbr3 ; 
 struct cnl_ddi_buf_trans const* icl_combo_phy_ddi_translations_hdmi ; 

__attribute__((used)) static const struct cnl_ddi_buf_trans *
icl_get_combo_buf_trans(struct drm_i915_private *dev_priv, int type, int rate,
			int *n_entries)
{
	if (type == INTEL_OUTPUT_HDMI) {
		*n_entries = ARRAY_SIZE(icl_combo_phy_ddi_translations_hdmi);
		return icl_combo_phy_ddi_translations_hdmi;
	} else if (rate > 540000 && type == INTEL_OUTPUT_EDP) {
		*n_entries = ARRAY_SIZE(icl_combo_phy_ddi_translations_edp_hbr3);
		return icl_combo_phy_ddi_translations_edp_hbr3;
	} else if (type == INTEL_OUTPUT_EDP && dev_priv->vbt.edp.low_vswing) {
		*n_entries = ARRAY_SIZE(icl_combo_phy_ddi_translations_edp_hbr2);
		return icl_combo_phy_ddi_translations_edp_hbr2;
	}

	*n_entries = ARRAY_SIZE(icl_combo_phy_ddi_translations_dp_hbr2);
	return icl_combo_phy_ddi_translations_dp_hbr2;
}