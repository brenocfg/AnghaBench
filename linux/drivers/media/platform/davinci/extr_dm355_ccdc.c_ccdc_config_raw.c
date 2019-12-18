#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int width; } ;
struct TYPE_6__ {unsigned int gamma_wd; scalar_t__ enable; } ;
struct TYPE_5__ {unsigned int horz_offset; unsigned int vert_offset; } ;
struct ccdc_config_params_raw {scalar_t__ data_sz; int lpf_enable; unsigned int datasft; unsigned int med_filt_thres; unsigned int mfilt1; unsigned int mfilt2; TYPE_2__ alaw; TYPE_1__ data_offset; int /*<<< orphan*/  col_pat_field1; int /*<<< orphan*/  col_pat_field0; int /*<<< orphan*/  csc; int /*<<< orphan*/  vertical_dft; int /*<<< orphan*/  blk_comp; int /*<<< orphan*/  blk_clamp; } ;
struct ccdc_params_raw {unsigned int vd_pol; unsigned int hd_pol; unsigned int fid_pol; unsigned int frm_fmt; unsigned int pix_fmt; unsigned int horz_flip_enable; scalar_t__ image_invert_enable; TYPE_3__ win; struct ccdc_config_params_raw config_params; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; struct ccdc_params_raw bayer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCDCFG ; 
 unsigned int CCDC_ALAW_ENABLE ; 
 unsigned int CCDC_ALAW_GAMMA_WD_MASK ; 
 unsigned int CCDC_CCDCFG_EXTRG_DISABLE ; 
 unsigned int CCDC_CCDCFG_FIDMD_LATCH_VSYNC ; 
 unsigned int CCDC_CCDCFG_TRGSEL_WEN ; 
 unsigned int CCDC_CCDCFG_WENLOG_AND ; 
 unsigned int CCDC_CFA_MOSAIC ; 
 unsigned int CCDC_DATAOFST_H_SHIFT ; 
 unsigned int CCDC_DATAOFST_MASK ; 
 unsigned int CCDC_DATAOFST_V_SHIFT ; 
 unsigned int CCDC_DATAPOL_NORMAL ; 
 unsigned int CCDC_DATASFT_MASK ; 
 unsigned int CCDC_DATASFT_SHIFT ; 
 scalar_t__ CCDC_DATA_8BITS ; 
 unsigned int CCDC_DATA_PACK_ENABLE ; 
 unsigned int CCDC_EXWEN_DISABLE ; 
 unsigned int CCDC_FID_POL_MASK ; 
 unsigned int CCDC_FID_POL_SHIFT ; 
 unsigned int CCDC_FRMFMT_INTERLACED ; 
 unsigned int CCDC_FRMFMT_PROGRESSIVE ; 
 unsigned int CCDC_FRM_FMT_MASK ; 
 unsigned int CCDC_FRM_FMT_SHIFT ; 
 unsigned int CCDC_GAMMAWD_INPUT_SHIFT ; 
 unsigned int CCDC_GAMMA_BITS_11_2 ; 
 unsigned int CCDC_HD_POL_MASK ; 
 unsigned int CCDC_HD_POL_SHIFT ; 
 unsigned int CCDC_HSIZE_FLIP_MASK ; 
 unsigned int CCDC_HSIZE_FLIP_SHIFT ; 
 int CCDC_HSIZE_VAL_MASK ; 
 unsigned int CCDC_LATCH_ON_VSYNC_DISABLE ; 
 unsigned int CCDC_LPF_MASK ; 
 unsigned int CCDC_LPF_SHIFT ; 
 unsigned int CCDC_MED_FILT_THRESH ; 
 unsigned int CCDC_MFILT1_SHIFT ; 
 unsigned int CCDC_MFILT2_SHIFT ; 
 unsigned int CCDC_PIX_FMT_MASK ; 
 unsigned int CCDC_PIX_FMT_SHIFT ; 
 unsigned int CCDC_RAW_IP_MODE ; 
 unsigned int CCDC_SDOFST_INTERLACE_INVERSE ; 
 unsigned int CCDC_SDOFST_INTERLACE_NORMAL ; 
 unsigned int CCDC_SDOFST_PROGRESSIVE_INVERSE ; 
 unsigned int CCDC_SDOFST_PROGRESSIVE_NORMAL ; 
 unsigned int CCDC_VDHDOUT_INPUT ; 
 unsigned int CCDC_VD_POL_MASK ; 
 unsigned int CCDC_VD_POL_SHIFT ; 
 unsigned int CCDC_YCINSWP_RAW ; 
 int /*<<< orphan*/  DATAOFST ; 
 int EFAULT ; 
 int /*<<< orphan*/  GAMMAWD ; 
 int /*<<< orphan*/  HSIZE ; 
 int /*<<< orphan*/  MEDFILT ; 
 int /*<<< orphan*/  MODESET ; 
 int /*<<< orphan*/  SDOFST ; 
 TYPE_4__ ccdc_cfg ; 
 int /*<<< orphan*/  ccdc_config_black_clamp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccdc_config_black_compense (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccdc_config_color_patterns (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccdc_config_csc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccdc_config_gain_offset () ; 
 scalar_t__ ccdc_config_vdfc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccdc_restore_defaults () ; 
 int /*<<< orphan*/  ccdc_setwin (TYPE_3__*,unsigned int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  regw (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccdc_config_raw(void)
{
	struct ccdc_params_raw *params = &ccdc_cfg.bayer;
	struct ccdc_config_params_raw *config_params =
					&ccdc_cfg.bayer.config_params;
	unsigned int val;

	dev_dbg(ccdc_cfg.dev, "\nStarting ccdc_config_raw...");

	/* restore power on defaults to register */
	ccdc_restore_defaults();

	/* CCDCFG register:
	 * set CCD Not to swap input since input is RAW data
	 * set FID detection function to Latch at V-Sync
	 * set WENLOG - ccdc valid area to AND
	 * set TRGSEL to WENBIT
	 * set EXTRG to DISABLE
	 * disable latching function on VSYNC - shadowed registers
	 */
	regw(CCDC_YCINSWP_RAW | CCDC_CCDCFG_FIDMD_LATCH_VSYNC |
	     CCDC_CCDCFG_WENLOG_AND | CCDC_CCDCFG_TRGSEL_WEN |
	     CCDC_CCDCFG_EXTRG_DISABLE | CCDC_LATCH_ON_VSYNC_DISABLE, CCDCFG);

	/*
	 * Set VDHD direction to input,  input type to raw input
	 * normal data polarity, do not use external WEN
	 */
	val = (CCDC_VDHDOUT_INPUT | CCDC_RAW_IP_MODE | CCDC_DATAPOL_NORMAL |
		CCDC_EXWEN_DISABLE);

	/*
	 * Configure the vertical sync polarity (MODESET.VDPOL), horizontal
	 * sync polarity (MODESET.HDPOL), field id polarity (MODESET.FLDPOL),
	 * frame format(progressive or interlace), & pixel format (Input mode)
	 */
	val |= (((params->vd_pol & CCDC_VD_POL_MASK) << CCDC_VD_POL_SHIFT) |
		((params->hd_pol & CCDC_HD_POL_MASK) << CCDC_HD_POL_SHIFT) |
		((params->fid_pol & CCDC_FID_POL_MASK) << CCDC_FID_POL_SHIFT) |
		((params->frm_fmt & CCDC_FRM_FMT_MASK) << CCDC_FRM_FMT_SHIFT) |
		((params->pix_fmt & CCDC_PIX_FMT_MASK) << CCDC_PIX_FMT_SHIFT));

	/* set pack for alaw compression */
	if ((config_params->data_sz == CCDC_DATA_8BITS) ||
	     config_params->alaw.enable)
		val |= CCDC_DATA_PACK_ENABLE;

	/* Configure for LPF */
	if (config_params->lpf_enable)
		val |= (config_params->lpf_enable & CCDC_LPF_MASK) <<
			CCDC_LPF_SHIFT;

	/* Configure the data shift */
	val |= (config_params->datasft & CCDC_DATASFT_MASK) <<
		CCDC_DATASFT_SHIFT;
	regw(val , MODESET);
	dev_dbg(ccdc_cfg.dev, "\nWriting 0x%x to MODESET...\n", val);

	/* Configure the Median Filter threshold */
	regw((config_params->med_filt_thres) & CCDC_MED_FILT_THRESH, MEDFILT);

	/* Configure GAMMAWD register. defaur 11-2, and Mosaic cfa pattern */
	val = CCDC_GAMMA_BITS_11_2 << CCDC_GAMMAWD_INPUT_SHIFT |
		CCDC_CFA_MOSAIC;

	/* Enable and configure aLaw register if needed */
	if (config_params->alaw.enable) {
		val |= (CCDC_ALAW_ENABLE |
			((config_params->alaw.gamma_wd &
			CCDC_ALAW_GAMMA_WD_MASK) <<
			CCDC_GAMMAWD_INPUT_SHIFT));
	}

	/* Configure Median filter1 & filter2 */
	val |= ((config_params->mfilt1 << CCDC_MFILT1_SHIFT) |
		(config_params->mfilt2 << CCDC_MFILT2_SHIFT));

	regw(val, GAMMAWD);
	dev_dbg(ccdc_cfg.dev, "\nWriting 0x%x to GAMMAWD...\n", val);

	/* configure video window */
	ccdc_setwin(&params->win, params->frm_fmt, 1);

	/* Optical Clamp Averaging */
	ccdc_config_black_clamp(&config_params->blk_clamp);

	/* Black level compensation */
	ccdc_config_black_compense(&config_params->blk_comp);

	/* Vertical Defect Correction if needed */
	if (ccdc_config_vdfc(&config_params->vertical_dft) < 0)
		return -EFAULT;

	/* color space conversion */
	ccdc_config_csc(&config_params->csc);

	/* color pattern */
	ccdc_config_color_patterns(&config_params->col_pat_field0,
				   &config_params->col_pat_field1);

	/* Configure the Gain  & offset control */
	ccdc_config_gain_offset();

	dev_dbg(ccdc_cfg.dev, "\nWriting %x to COLPTN...\n", val);

	/* Configure DATAOFST  register */
	val = (config_params->data_offset.horz_offset & CCDC_DATAOFST_MASK) <<
		CCDC_DATAOFST_H_SHIFT;
	val |= (config_params->data_offset.vert_offset & CCDC_DATAOFST_MASK) <<
		CCDC_DATAOFST_V_SHIFT;
	regw(val, DATAOFST);

	/* configuring HSIZE register */
	val = (params->horz_flip_enable & CCDC_HSIZE_FLIP_MASK) <<
		CCDC_HSIZE_FLIP_SHIFT;

	/* If pack 8 is enable then 1 pixel will take 1 byte */
	if ((config_params->data_sz == CCDC_DATA_8BITS) ||
	     config_params->alaw.enable) {
		val |= (((params->win.width) + 31) >> 5) &
			CCDC_HSIZE_VAL_MASK;

		/* adjust to multiple of 32 */
		dev_dbg(ccdc_cfg.dev, "\nWriting 0x%x to HSIZE...\n",
		       (((params->win.width) + 31) >> 5) &
			CCDC_HSIZE_VAL_MASK);
	} else {
		/* else one pixel will take 2 byte */
		val |= (((params->win.width * 2) + 31) >> 5) &
			CCDC_HSIZE_VAL_MASK;

		dev_dbg(ccdc_cfg.dev, "\nWriting 0x%x to HSIZE...\n",
		       (((params->win.width * 2) + 31) >> 5) &
			CCDC_HSIZE_VAL_MASK);
	}
	regw(val, HSIZE);

	/* Configure SDOFST register */
	if (params->frm_fmt == CCDC_FRMFMT_INTERLACED) {
		if (params->image_invert_enable) {
			/* For interlace inverse mode */
			regw(CCDC_SDOFST_INTERLACE_INVERSE, SDOFST);
			dev_dbg(ccdc_cfg.dev, "\nWriting %x to SDOFST...\n",
				CCDC_SDOFST_INTERLACE_INVERSE);
		} else {
			/* For interlace non inverse mode */
			regw(CCDC_SDOFST_INTERLACE_NORMAL, SDOFST);
			dev_dbg(ccdc_cfg.dev, "\nWriting %x to SDOFST...\n",
				CCDC_SDOFST_INTERLACE_NORMAL);
		}
	} else if (params->frm_fmt == CCDC_FRMFMT_PROGRESSIVE) {
		if (params->image_invert_enable) {
			/* For progessive inverse mode */
			regw(CCDC_SDOFST_PROGRESSIVE_INVERSE, SDOFST);
			dev_dbg(ccdc_cfg.dev, "\nWriting %x to SDOFST...\n",
				CCDC_SDOFST_PROGRESSIVE_INVERSE);
		} else {
			/* For progessive non inverse mode */
			regw(CCDC_SDOFST_PROGRESSIVE_NORMAL, SDOFST);
			dev_dbg(ccdc_cfg.dev, "\nWriting %x to SDOFST...\n",
				CCDC_SDOFST_PROGRESSIVE_NORMAL);
		}
	}
	dev_dbg(ccdc_cfg.dev, "\nend of ccdc_config_raw...");
	return 0;
}