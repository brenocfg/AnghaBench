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
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int DP_TRAIN_VOLTAGE_SWING_MASK ; 
 int /*<<< orphan*/  INTEL_OUTPUT_EDP ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 scalar_t__ IS_ICELAKE (struct drm_i915_private*) ; 
 int PORT_A ; 
 int PORT_B ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  bxt_get_buf_trans_dp (struct drm_i915_private*,int*) ; 
 int /*<<< orphan*/  bxt_get_buf_trans_edp (struct drm_i915_private*,int*) ; 
 int /*<<< orphan*/  cnl_get_buf_trans_dp (struct drm_i915_private*,int*) ; 
 int /*<<< orphan*/  cnl_get_buf_trans_edp (struct drm_i915_private*,int*) ; 
 int /*<<< orphan*/  icl_get_combo_buf_trans (struct drm_i915_private*,int,int /*<<< orphan*/ ,int*) ; 
 int* icl_mg_phy_ddi_translations ; 
 int* index_to_dp_signal_levels ; 
 int /*<<< orphan*/  intel_ddi_get_buf_trans_dp (struct drm_i915_private*,int,int*) ; 
 int /*<<< orphan*/  intel_ddi_get_buf_trans_edp (struct drm_i915_private*,int,int*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

u8 intel_ddi_dp_voltage_max(struct intel_encoder *encoder)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);
	enum port port = encoder->port;
	int n_entries;

	if (IS_ICELAKE(dev_priv)) {
		if (port == PORT_A || port == PORT_B)
			icl_get_combo_buf_trans(dev_priv, port, encoder->type,
						&n_entries);
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