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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {int port; int /*<<< orphan*/  type; TYPE_1__ base; } ;
struct intel_dp {int /*<<< orphan*/  link_rate; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;
typedef  enum phy { ____Placeholder_phy } phy ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int DP_TRAIN_VOLTAGE_SWING_MASK ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INTEL_OUTPUT_EDP ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  bxt_get_buf_trans_dp (struct drm_i915_private*,int*) ; 
 int /*<<< orphan*/  bxt_get_buf_trans_edp (struct drm_i915_private*,int*) ; 
 int /*<<< orphan*/  cnl_get_buf_trans_dp (struct drm_i915_private*,int*) ; 
 int /*<<< orphan*/  cnl_get_buf_trans_edp (struct drm_i915_private*,int*) ; 
 struct intel_dp* enc_to_intel_dp (TYPE_1__*) ; 
 int /*<<< orphan*/  icl_get_combo_buf_trans (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int* icl_mg_phy_ddi_translations ; 
 int* index_to_dp_signal_levels ; 
 int /*<<< orphan*/  intel_ddi_get_buf_trans_dp (struct drm_i915_private*,int,int*) ; 
 int /*<<< orphan*/  intel_ddi_get_buf_trans_edp (struct drm_i915_private*,int,int*) ; 
 scalar_t__ intel_phy_is_combo (struct drm_i915_private*,int) ; 
 int intel_port_to_phy (struct drm_i915_private*,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

u8 intel_ddi_dp_voltage_max(struct intel_encoder *encoder)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	struct intel_dp *intel_dp = enc_to_intel_dp(&encoder->base);
	enum port port = encoder->port;
	enum phy phy = intel_port_to_phy(dev_priv, port);
	int n_entries;

	if (INTEL_GEN(dev_priv) >= 11) {
		if (intel_phy_is_combo(dev_priv, phy))
			icl_get_combo_buf_trans(dev_priv, encoder->type,
						intel_dp->link_rate, &n_entries);
		else
			n_entries = ARRAY_SIZE(icl_mg_phy_ddi_translations);
	} else if (IS_CANNONLAKE(dev_priv)) {
		if (encoder->type == INTEL_OUTPUT_EDP)
			cnl_get_buf_trans_edp(dev_priv, &n_entries);
		else
			cnl_get_buf_trans_dp(dev_priv, &n_entries);
	} else if (IS_GEN9_LP(dev_priv)) {
		if (encoder->type == INTEL_OUTPUT_EDP)
			bxt_get_buf_trans_edp(dev_priv, &n_entries);
		else
			bxt_get_buf_trans_dp(dev_priv, &n_entries);
	} else {
		if (encoder->type == INTEL_OUTPUT_EDP)
			intel_ddi_get_buf_trans_edp(dev_priv, port, &n_entries);
		else
			intel_ddi_get_buf_trans_dp(dev_priv, port, &n_entries);
	}

	if (WARN_ON(n_entries < 1))
		n_entries = 1;
	if (WARN_ON(n_entries > ARRAY_SIZE(index_to_dp_signal_levels)))
		n_entries = ARRAY_SIZE(index_to_dp_signal_levels);

	return index_to_dp_signal_levels[n_entries - 1] &
		DP_TRAIN_VOLTAGE_SWING_MASK;
}