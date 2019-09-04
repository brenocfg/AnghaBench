#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct edp_power_seq {int dummy; } ;
struct edp_fast_link_params {int rate; int lanes; int preemphasis; int vswing; } ;
struct TYPE_4__ {int bpp; int lanes; int low_vswing; int /*<<< orphan*/  vswing; int /*<<< orphan*/  preemphasis; int /*<<< orphan*/  rate; struct edp_power_seq pps; } ;
struct TYPE_5__ {int panel_type; TYPE_1__ edp; } ;
struct drm_i915_private {TYPE_2__ vbt; } ;
struct bdb_header {int version; } ;
struct bdb_edp {int color_depth; int edp_vswing_preemph; struct edp_fast_link_params* fast_link_params; struct edp_power_seq* power_seqs; } ;
struct TYPE_6__ {int edp_vswing; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDB_EDP ; 
 int /*<<< orphan*/  DP_LINK_BW_1_62 ; 
 int /*<<< orphan*/  DP_LINK_BW_2_7 ; 
 int /*<<< orphan*/  DP_TRAIN_PRE_EMPH_LEVEL_0 ; 
 int /*<<< orphan*/  DP_TRAIN_PRE_EMPH_LEVEL_1 ; 
 int /*<<< orphan*/  DP_TRAIN_PRE_EMPH_LEVEL_2 ; 
 int /*<<< orphan*/  DP_TRAIN_PRE_EMPH_LEVEL_3 ; 
 int /*<<< orphan*/  DP_TRAIN_VOLTAGE_SWING_LEVEL_0 ; 
 int /*<<< orphan*/  DP_TRAIN_VOLTAGE_SWING_LEVEL_1 ; 
 int /*<<< orphan*/  DP_TRAIN_VOLTAGE_SWING_LEVEL_2 ; 
 int /*<<< orphan*/  DP_TRAIN_VOLTAGE_SWING_LEVEL_3 ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
#define  EDP_18BPP 143 
#define  EDP_24BPP 142 
#define  EDP_30BPP 141 
#define  EDP_LANE_1 140 
#define  EDP_LANE_2 139 
#define  EDP_LANE_4 138 
#define  EDP_PREEMPHASIS_3_5dB 137 
#define  EDP_PREEMPHASIS_6dB 136 
#define  EDP_PREEMPHASIS_9_5dB 135 
#define  EDP_PREEMPHASIS_NONE 134 
#define  EDP_RATE_1_62 133 
#define  EDP_RATE_2_7 132 
#define  EDP_VSWING_0_4V 131 
#define  EDP_VSWING_0_6V 130 
#define  EDP_VSWING_0_8V 129 
#define  EDP_VSWING_1_2V 128 
 struct bdb_edp* find_section (struct bdb_header const*,int /*<<< orphan*/ ) ; 
 TYPE_3__ i915_modparams ; 

__attribute__((used)) static void
parse_edp(struct drm_i915_private *dev_priv, const struct bdb_header *bdb)
{
	const struct bdb_edp *edp;
	const struct edp_power_seq *edp_pps;
	const struct edp_fast_link_params *edp_link_params;
	int panel_type = dev_priv->vbt.panel_type;

	edp = find_section(bdb, BDB_EDP);
	if (!edp)
		return;

	switch ((edp->color_depth >> (panel_type * 2)) & 3) {
	case EDP_18BPP:
		dev_priv->vbt.edp.bpp = 18;
		break;
	case EDP_24BPP:
		dev_priv->vbt.edp.bpp = 24;
		break;
	case EDP_30BPP:
		dev_priv->vbt.edp.bpp = 30;
		break;
	}

	/* Get the eDP sequencing and link info */
	edp_pps = &edp->power_seqs[panel_type];
	edp_link_params = &edp->fast_link_params[panel_type];

	dev_priv->vbt.edp.pps = *edp_pps;

	switch (edp_link_params->rate) {
	case EDP_RATE_1_62:
		dev_priv->vbt.edp.rate = DP_LINK_BW_1_62;
		break;
	case EDP_RATE_2_7:
		dev_priv->vbt.edp.rate = DP_LINK_BW_2_7;
		break;
	default:
		DRM_DEBUG_KMS("VBT has unknown eDP link rate value %u\n",
			      edp_link_params->rate);
		break;
	}

	switch (edp_link_params->lanes) {
	case EDP_LANE_1:
		dev_priv->vbt.edp.lanes = 1;
		break;
	case EDP_LANE_2:
		dev_priv->vbt.edp.lanes = 2;
		break;
	case EDP_LANE_4:
		dev_priv->vbt.edp.lanes = 4;
		break;
	default:
		DRM_DEBUG_KMS("VBT has unknown eDP lane count value %u\n",
			      edp_link_params->lanes);
		break;
	}

	switch (edp_link_params->preemphasis) {
	case EDP_PREEMPHASIS_NONE:
		dev_priv->vbt.edp.preemphasis = DP_TRAIN_PRE_EMPH_LEVEL_0;
		break;
	case EDP_PREEMPHASIS_3_5dB:
		dev_priv->vbt.edp.preemphasis = DP_TRAIN_PRE_EMPH_LEVEL_1;
		break;
	case EDP_PREEMPHASIS_6dB:
		dev_priv->vbt.edp.preemphasis = DP_TRAIN_PRE_EMPH_LEVEL_2;
		break;
	case EDP_PREEMPHASIS_9_5dB:
		dev_priv->vbt.edp.preemphasis = DP_TRAIN_PRE_EMPH_LEVEL_3;
		break;
	default:
		DRM_DEBUG_KMS("VBT has unknown eDP pre-emphasis value %u\n",
			      edp_link_params->preemphasis);
		break;
	}

	switch (edp_link_params->vswing) {
	case EDP_VSWING_0_4V:
		dev_priv->vbt.edp.vswing = DP_TRAIN_VOLTAGE_SWING_LEVEL_0;
		break;
	case EDP_VSWING_0_6V:
		dev_priv->vbt.edp.vswing = DP_TRAIN_VOLTAGE_SWING_LEVEL_1;
		break;
	case EDP_VSWING_0_8V:
		dev_priv->vbt.edp.vswing = DP_TRAIN_VOLTAGE_SWING_LEVEL_2;
		break;
	case EDP_VSWING_1_2V:
		dev_priv->vbt.edp.vswing = DP_TRAIN_VOLTAGE_SWING_LEVEL_3;
		break;
	default:
		DRM_DEBUG_KMS("VBT has unknown eDP voltage swing value %u\n",
			      edp_link_params->vswing);
		break;
	}

	if (bdb->version >= 173) {
		u8 vswing;

		/* Don't read from VBT if module parameter has valid value*/
		if (i915_modparams.edp_vswing) {
			dev_priv->vbt.edp.low_vswing =
				i915_modparams.edp_vswing == 1;
		} else {
			vswing = (edp->edp_vswing_preemph >> (panel_type * 4)) & 0xF;
			dev_priv->vbt.edp.low_vswing = vswing == 0;
		}
	}
}