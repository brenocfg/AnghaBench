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
struct lvds_fp_timing {scalar_t__ x_res; scalar_t__ y_res; int lvds_reg_val; } ;
struct lvds_dvo_timing {int dummy; } ;
struct TYPE_2__ {int panel_type; int bios_lvds_val; struct drm_display_mode* lfp_lvds_vbt_mode; int /*<<< orphan*/  drrs_type; int /*<<< orphan*/  lvds_dither; } ;
struct drm_i915_private {TYPE_1__ vbt; } ;
struct drm_display_mode {scalar_t__ hdisplay; scalar_t__ vdisplay; } ;
struct bdb_lvds_options {int panel_type; int dps_panel_type_bits; int /*<<< orphan*/  pixel_dither; } ;
struct bdb_lvds_lfp_data_ptrs {int dummy; } ;
struct bdb_lvds_lfp_data {int dummy; } ;
struct bdb_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDB_LVDS_LFP_DATA ; 
 int /*<<< orphan*/  BDB_LVDS_LFP_DATA_PTRS ; 
 int /*<<< orphan*/  BDB_LVDS_OPTIONS ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  DRRS_NOT_SUPPORTED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MODE_MASK ; 
 int /*<<< orphan*/  SEAMLESS_DRRS_SUPPORT ; 
 int /*<<< orphan*/  STATIC_DRRS_SUPPORT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  drm_mode_debug_printmodeline (struct drm_display_mode*) ; 
 int /*<<< orphan*/  fill_detail_timing_data (struct drm_display_mode*,struct lvds_dvo_timing const*) ; 
 void* find_section (struct bdb_header const*,int /*<<< orphan*/ ) ; 
 struct lvds_dvo_timing* get_lvds_dvo_timing (struct bdb_lvds_lfp_data const*,struct bdb_lvds_lfp_data_ptrs const*,int) ; 
 struct lvds_fp_timing* get_lvds_fp_timing (struct bdb_header const*,struct bdb_lvds_lfp_data const*,struct bdb_lvds_lfp_data_ptrs const*,int) ; 
 int intel_opregion_get_panel_type (struct drm_i915_private*) ; 
 struct drm_display_mode* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
parse_lfp_panel_data(struct drm_i915_private *dev_priv,
		     const struct bdb_header *bdb)
{
	const struct bdb_lvds_options *lvds_options;
	const struct bdb_lvds_lfp_data *lvds_lfp_data;
	const struct bdb_lvds_lfp_data_ptrs *lvds_lfp_data_ptrs;
	const struct lvds_dvo_timing *panel_dvo_timing;
	const struct lvds_fp_timing *fp_timing;
	struct drm_display_mode *panel_fixed_mode;
	int panel_type;
	int drrs_mode;
	int ret;

	lvds_options = find_section(bdb, BDB_LVDS_OPTIONS);
	if (!lvds_options)
		return;

	dev_priv->vbt.lvds_dither = lvds_options->pixel_dither;

	ret = intel_opregion_get_panel_type(dev_priv);
	if (ret >= 0) {
		WARN_ON(ret > 0xf);
		panel_type = ret;
		DRM_DEBUG_KMS("Panel type: %d (OpRegion)\n", panel_type);
	} else {
		if (lvds_options->panel_type > 0xf) {
			DRM_DEBUG_KMS("Invalid VBT panel type 0x%x\n",
				      lvds_options->panel_type);
			return;
		}
		panel_type = lvds_options->panel_type;
		DRM_DEBUG_KMS("Panel type: %d (VBT)\n", panel_type);
	}

	dev_priv->vbt.panel_type = panel_type;

	drrs_mode = (lvds_options->dps_panel_type_bits
				>> (panel_type * 2)) & MODE_MASK;
	/*
	 * VBT has static DRRS = 0 and seamless DRRS = 2.
	 * The below piece of code is required to adjust vbt.drrs_type
	 * to match the enum drrs_support_type.
	 */
	switch (drrs_mode) {
	case 0:
		dev_priv->vbt.drrs_type = STATIC_DRRS_SUPPORT;
		DRM_DEBUG_KMS("DRRS supported mode is static\n");
		break;
	case 2:
		dev_priv->vbt.drrs_type = SEAMLESS_DRRS_SUPPORT;
		DRM_DEBUG_KMS("DRRS supported mode is seamless\n");
		break;
	default:
		dev_priv->vbt.drrs_type = DRRS_NOT_SUPPORTED;
		DRM_DEBUG_KMS("DRRS not supported (VBT input)\n");
		break;
	}

	lvds_lfp_data = find_section(bdb, BDB_LVDS_LFP_DATA);
	if (!lvds_lfp_data)
		return;

	lvds_lfp_data_ptrs = find_section(bdb, BDB_LVDS_LFP_DATA_PTRS);
	if (!lvds_lfp_data_ptrs)
		return;

	panel_dvo_timing = get_lvds_dvo_timing(lvds_lfp_data,
					       lvds_lfp_data_ptrs,
					       panel_type);

	panel_fixed_mode = kzalloc(sizeof(*panel_fixed_mode), GFP_KERNEL);
	if (!panel_fixed_mode)
		return;

	fill_detail_timing_data(panel_fixed_mode, panel_dvo_timing);

	dev_priv->vbt.lfp_lvds_vbt_mode = panel_fixed_mode;

	DRM_DEBUG_KMS("Found panel mode in BIOS VBT tables:\n");
	drm_mode_debug_printmodeline(panel_fixed_mode);

	fp_timing = get_lvds_fp_timing(bdb, lvds_lfp_data,
				       lvds_lfp_data_ptrs,
				       panel_type);
	if (fp_timing) {
		/* check the resolution, just to be sure */
		if (fp_timing->x_res == panel_fixed_mode->hdisplay &&
		    fp_timing->y_res == panel_fixed_mode->vdisplay) {
			dev_priv->vbt.bios_lvds_val = fp_timing->lvds_reg_val;
			DRM_DEBUG_KMS("VBT initial LVDS value %x\n",
				      dev_priv->vbt.bios_lvds_val);
		}
	}
}