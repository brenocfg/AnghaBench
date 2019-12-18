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
typedef  size_t u32 ;
struct TYPE_4__ {int flags; } ;
struct sti_hda {int enabled; TYPE_2__ mode; int /*<<< orphan*/  clk_hddac; int /*<<< orphan*/  clk_pix; } ;
struct drm_bridge {struct sti_hda* driver_private; } ;
struct TYPE_3__ {int vid_cat; int /*<<< orphan*/  nb_instr; int /*<<< orphan*/  awg_instr; } ;

/* Variables and functions */
 size_t CFG_AWG_ASYNC_EN ; 
 size_t CFG_AWG_ASYNC_VSYNC_MTD ; 
 size_t CFG_AWG_FLTR_MODE_ED ; 
 size_t CFG_AWG_FLTR_MODE_HD ; 
 size_t CFG_PBPR_SYNC_OFF_SHIFT ; 
 size_t CFG_PBPR_SYNC_OFF_VAL ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 scalar_t__ HDA_ANA_CFG ; 
 scalar_t__ HDA_ANA_SCALE_CTRL_CB ; 
 scalar_t__ HDA_ANA_SCALE_CTRL_CR ; 
 scalar_t__ HDA_ANA_SCALE_CTRL_Y ; 
 scalar_t__ HDA_ANA_SRC_C_CFG ; 
 size_t HDA_ANA_SRC_C_CFG_4X ; 
 size_t HDA_ANA_SRC_C_CFG_ALT_2X ; 
 scalar_t__ HDA_ANA_SRC_Y_CFG ; 
 size_t HDA_ANA_SRC_Y_CFG_4X ; 
 size_t HDA_ANA_SRC_Y_CFG_ALT_2X ; 
 scalar_t__ HDA_COEFF_C_PH1_TAP123 ; 
 scalar_t__ HDA_COEFF_Y_PH1_TAP123 ; 
 size_t SAMPLER_COEF_NB ; 
 size_t SCALE_CTRL_CB_DFLT ; 
 size_t SCALE_CTRL_CR_DFLT ; 
 size_t SCALE_CTRL_Y_DFLT ; 
#define  VID_ED 131 
#define  VID_HD_148M 130 
#define  VID_HD_74M 129 
#define  VID_SD 128 
 scalar_t__ clk_prepare_enable (int /*<<< orphan*/ ) ; 
 size_t* coef_c_alt_2x ; 
 size_t* coef_y_alt_2x ; 
 size_t* coef_yc_4x ; 
 int /*<<< orphan*/  hda_enable_hd_dacs (struct sti_hda*,int) ; 
 int /*<<< orphan*/  hda_get_mode_idx (TYPE_2__,size_t*) ; 
 size_t hda_read (struct sti_hda*,scalar_t__) ; 
 TYPE_1__* hda_supported_modes ; 
 int /*<<< orphan*/  hda_write (struct sti_hda*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  sti_hda_configure_awg (struct sti_hda*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sti_hda_pre_enable(struct drm_bridge *bridge)
{
	struct sti_hda *hda = bridge->driver_private;
	u32 val, i, mode_idx;
	u32 src_filter_y, src_filter_c;
	u32 *coef_y, *coef_c;
	u32 filter_mode;

	DRM_DEBUG_DRIVER("\n");

	if (hda->enabled)
		return;

	/* Prepare/enable clocks */
	if (clk_prepare_enable(hda->clk_pix))
		DRM_ERROR("Failed to prepare/enable hda_pix clk\n");
	if (clk_prepare_enable(hda->clk_hddac))
		DRM_ERROR("Failed to prepare/enable hda_hddac clk\n");

	if (!hda_get_mode_idx(hda->mode, &mode_idx)) {
		DRM_ERROR("Undefined mode\n");
		return;
	}

	switch (hda_supported_modes[mode_idx].vid_cat) {
	case VID_HD_148M:
		DRM_ERROR("Beyond HD analog capabilities\n");
		return;
	case VID_HD_74M:
		/* HD use alternate 2x filter */
		filter_mode = CFG_AWG_FLTR_MODE_HD;
		src_filter_y = HDA_ANA_SRC_Y_CFG_ALT_2X;
		src_filter_c = HDA_ANA_SRC_C_CFG_ALT_2X;
		coef_y = coef_y_alt_2x;
		coef_c = coef_c_alt_2x;
		break;
	case VID_ED:
		/* ED uses 4x filter */
		filter_mode = CFG_AWG_FLTR_MODE_ED;
		src_filter_y = HDA_ANA_SRC_Y_CFG_4X;
		src_filter_c = HDA_ANA_SRC_C_CFG_4X;
		coef_y = coef_yc_4x;
		coef_c = coef_yc_4x;
		break;
	case VID_SD:
		DRM_ERROR("Not supported\n");
		return;
	default:
		DRM_ERROR("Undefined resolution\n");
		return;
	}
	DRM_DEBUG_DRIVER("Using HDA mode #%d\n", mode_idx);

	/* Enable HD Video DACs */
	hda_enable_hd_dacs(hda, true);

	/* Configure scaler */
	hda_write(hda, SCALE_CTRL_Y_DFLT, HDA_ANA_SCALE_CTRL_Y);
	hda_write(hda, SCALE_CTRL_CB_DFLT, HDA_ANA_SCALE_CTRL_CB);
	hda_write(hda, SCALE_CTRL_CR_DFLT, HDA_ANA_SCALE_CTRL_CR);

	/* Configure sampler */
	hda_write(hda , src_filter_y, HDA_ANA_SRC_Y_CFG);
	hda_write(hda, src_filter_c,  HDA_ANA_SRC_C_CFG);
	for (i = 0; i < SAMPLER_COEF_NB; i++) {
		hda_write(hda, coef_y[i], HDA_COEFF_Y_PH1_TAP123 + i * 4);
		hda_write(hda, coef_c[i], HDA_COEFF_C_PH1_TAP123 + i * 4);
	}

	/* Configure main HDFormatter */
	val = 0;
	val |= (hda->mode.flags & DRM_MODE_FLAG_INTERLACE) ?
	    0 : CFG_AWG_ASYNC_VSYNC_MTD;
	val |= (CFG_PBPR_SYNC_OFF_VAL << CFG_PBPR_SYNC_OFF_SHIFT);
	val |= filter_mode;
	hda_write(hda, val, HDA_ANA_CFG);

	/* Configure AWG */
	sti_hda_configure_awg(hda, hda_supported_modes[mode_idx].awg_instr,
			      hda_supported_modes[mode_idx].nb_instr);

	/* Enable AWG */
	val = hda_read(hda, HDA_ANA_CFG);
	val |= CFG_AWG_ASYNC_EN;
	hda_write(hda, val, HDA_ANA_CFG);

	hda->enabled = true;
}