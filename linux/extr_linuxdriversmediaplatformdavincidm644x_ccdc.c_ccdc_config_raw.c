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
struct TYPE_5__ {unsigned int left; unsigned int width; unsigned int top; unsigned int height; } ;
struct TYPE_4__ {unsigned int gamma_wd; scalar_t__ enable; } ;
struct ccdc_config_params_raw {unsigned int data_sz; TYPE_1__ alaw; int /*<<< orphan*/  blk_comp; int /*<<< orphan*/  blk_clamp; } ;
struct ccdc_params_raw {unsigned int vd_pol; unsigned int hd_pol; unsigned int fid_pol; unsigned int frm_fmt; unsigned int pix_fmt; TYPE_2__ win; scalar_t__ image_invert_enable; struct ccdc_config_params_raw config_params; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; struct ccdc_params_raw bayer; } ;

/* Variables and functions */
 unsigned int CCDC_32BYTE_ALIGN_VAL ; 
 int /*<<< orphan*/  CCDC_ALAW ; 
 unsigned int CCDC_ALAW_ENABLE ; 
 unsigned int CCDC_ALAW_GAMMA_WD_MASK ; 
 int /*<<< orphan*/  CCDC_CCDCFG ; 
 int /*<<< orphan*/  CCDC_COLPTN ; 
 unsigned int CCDC_COLPTN_VAL ; 
 unsigned int CCDC_DATA_10BITS ; 
 unsigned int CCDC_DATA_8BITS ; 
 unsigned int CCDC_DATA_PACK_ENABLE ; 
 unsigned int CCDC_DATA_SZ_MASK ; 
 unsigned int CCDC_DATA_SZ_SHIFT ; 
 unsigned int CCDC_DISABLE_VIDEO_PORT ; 
 unsigned int CCDC_FID_POL_MASK ; 
 unsigned int CCDC_FID_POL_SHIFT ; 
 int /*<<< orphan*/  CCDC_FMTCFG ; 
 unsigned int CCDC_FMTCFG_VPIN_MASK ; 
 unsigned int CCDC_FMTCFG_VPIN_SHIFT ; 
 int /*<<< orphan*/  CCDC_FMT_HORZ ; 
 unsigned int CCDC_FMT_HORZ_FMTLNH_MASK ; 
 unsigned int CCDC_FMT_HORZ_FMTSPH_MASK ; 
 unsigned int CCDC_FMT_HORZ_FMTSPH_SHIFT ; 
 int /*<<< orphan*/  CCDC_FMT_VERT ; 
 unsigned int CCDC_FMT_VERT_FMTLNV_MASK ; 
 unsigned int CCDC_FMT_VERT_FMTSLV_MASK ; 
 unsigned int CCDC_FMT_VERT_FMTSLV_SHIFT ; 
 unsigned int CCDC_FRMFMT_INTERLACED ; 
 unsigned int CCDC_FRMFMT_PROGRESSIVE ; 
 unsigned int CCDC_FRM_FMT_MASK ; 
 unsigned int CCDC_FRM_FMT_SHIFT ; 
 unsigned int CCDC_HD_POL_MASK ; 
 unsigned int CCDC_HD_POL_SHIFT ; 
 int /*<<< orphan*/  CCDC_HSIZE_OFF ; 
 unsigned int CCDC_HSIZE_OFF_MASK ; 
 int CCDC_INTERLACED_HEIGHT_SHIFT ; 
 unsigned int CCDC_INTERLACED_IMAGE_INVERT ; 
 unsigned int CCDC_INTERLACED_NO_IMAGE_INVERT ; 
 unsigned int CCDC_LATCH_ON_VSYNC_DISABLE ; 
 unsigned int CCDC_PIX_FMT_MASK ; 
 unsigned int CCDC_PIX_FMT_SHIFT ; 
 int /*<<< orphan*/  CCDC_PPC_RAW ; 
 unsigned int CCDC_PROGRESSIVE_NO_IMAGE_INVERT ; 
 int /*<<< orphan*/  CCDC_SDOFST ; 
 int /*<<< orphan*/  CCDC_SYN_MODE ; 
 unsigned int CCDC_TWO_BYTES_PER_PIXEL ; 
 unsigned int CCDC_VDHDEN_ENABLE ; 
 unsigned int CCDC_VD_POL_MASK ; 
 unsigned int CCDC_VD_POL_SHIFT ; 
 int /*<<< orphan*/  CCDC_VP_OUT ; 
 unsigned int CCDC_VP_OUT_HORZ_NUM_MASK ; 
 unsigned int CCDC_VP_OUT_HORZ_NUM_SHIFT ; 
 unsigned int CCDC_VP_OUT_HORZ_ST_MASK ; 
 int CCDC_VP_OUT_VERT_NUM_MASK ; 
 int CCDC_VP_OUT_VERT_NUM_SHIFT ; 
 unsigned int CCDC_WEN_ENABLE ; 
 TYPE_3__ ccdc_cfg ; 
 int /*<<< orphan*/  ccdc_config_black_clamp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccdc_config_black_compense (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccdc_readregs () ; 
 int /*<<< orphan*/  ccdc_restore_defaults () ; 
 int /*<<< orphan*/  ccdc_sbl_reset () ; 
 int /*<<< orphan*/  ccdc_setwin (TYPE_2__*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  regw (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccdc_config_raw(void)
{
	struct ccdc_params_raw *params = &ccdc_cfg.bayer;
	struct ccdc_config_params_raw *config_params =
				&ccdc_cfg.bayer.config_params;
	unsigned int syn_mode = 0;
	unsigned int val;

	dev_dbg(ccdc_cfg.dev, "\nStarting ccdc_config_raw...");

	/*      Reset CCDC */
	ccdc_restore_defaults();

	/* Disable latching function registers on VSYNC  */
	regw(CCDC_LATCH_ON_VSYNC_DISABLE, CCDC_CCDCFG);

	/*
	 * Configure the vertical sync polarity(SYN_MODE.VDPOL),
	 * horizontal sync polarity (SYN_MODE.HDPOL), frame id polarity
	 * (SYN_MODE.FLDPOL), frame format(progressive or interlace),
	 * data size(SYNMODE.DATSIZ), &pixel format (Input mode), output
	 * SDRAM, enable internal timing generator
	 */
	syn_mode =
		(((params->vd_pol & CCDC_VD_POL_MASK) << CCDC_VD_POL_SHIFT) |
		((params->hd_pol & CCDC_HD_POL_MASK) << CCDC_HD_POL_SHIFT) |
		((params->fid_pol & CCDC_FID_POL_MASK) << CCDC_FID_POL_SHIFT) |
		((params->frm_fmt & CCDC_FRM_FMT_MASK) << CCDC_FRM_FMT_SHIFT) |
		((config_params->data_sz & CCDC_DATA_SZ_MASK) <<
		CCDC_DATA_SZ_SHIFT) |
		((params->pix_fmt & CCDC_PIX_FMT_MASK) << CCDC_PIX_FMT_SHIFT) |
		CCDC_WEN_ENABLE | CCDC_VDHDEN_ENABLE);

	/* Enable and configure aLaw register if needed */
	if (config_params->alaw.enable) {
		val = ((config_params->alaw.gamma_wd &
		      CCDC_ALAW_GAMMA_WD_MASK) | CCDC_ALAW_ENABLE);
		regw(val, CCDC_ALAW);
		dev_dbg(ccdc_cfg.dev, "\nWriting 0x%x to ALAW...\n", val);
	}

	/* Configure video window */
	ccdc_setwin(&params->win, params->frm_fmt, CCDC_PPC_RAW);

	/* Configure Black Clamp */
	ccdc_config_black_clamp(&config_params->blk_clamp);

	/* Configure Black level compensation */
	ccdc_config_black_compense(&config_params->blk_comp);

	/* If data size is 8 bit then pack the data */
	if ((config_params->data_sz == CCDC_DATA_8BITS) ||
	     config_params->alaw.enable)
		syn_mode |= CCDC_DATA_PACK_ENABLE;

	/* disable video port */
	val = CCDC_DISABLE_VIDEO_PORT;

	if (config_params->data_sz == CCDC_DATA_8BITS)
		val |= (CCDC_DATA_10BITS & CCDC_FMTCFG_VPIN_MASK)
		    << CCDC_FMTCFG_VPIN_SHIFT;
	else
		val |= (config_params->data_sz & CCDC_FMTCFG_VPIN_MASK)
		    << CCDC_FMTCFG_VPIN_SHIFT;
	/* Write value in FMTCFG */
	regw(val, CCDC_FMTCFG);

	dev_dbg(ccdc_cfg.dev, "\nWriting 0x%x to FMTCFG...\n", val);
	/* Configure the color pattern according to mt9t001 sensor */
	regw(CCDC_COLPTN_VAL, CCDC_COLPTN);

	dev_dbg(ccdc_cfg.dev, "\nWriting 0xBB11BB11 to COLPTN...\n");
	/*
	 * Configure Data formatter(Video port) pixel selection
	 * (FMT_HORZ, FMT_VERT)
	 */
	val = ((params->win.left & CCDC_FMT_HORZ_FMTSPH_MASK) <<
	      CCDC_FMT_HORZ_FMTSPH_SHIFT) |
	      (params->win.width & CCDC_FMT_HORZ_FMTLNH_MASK);
	regw(val, CCDC_FMT_HORZ);

	dev_dbg(ccdc_cfg.dev, "\nWriting 0x%x to FMT_HORZ...\n", val);
	val = (params->win.top & CCDC_FMT_VERT_FMTSLV_MASK)
	    << CCDC_FMT_VERT_FMTSLV_SHIFT;
	if (params->frm_fmt == CCDC_FRMFMT_PROGRESSIVE)
		val |= (params->win.height) & CCDC_FMT_VERT_FMTLNV_MASK;
	else
		val |= (params->win.height >> 1) & CCDC_FMT_VERT_FMTLNV_MASK;

	dev_dbg(ccdc_cfg.dev, "\nparams->win.height  0x%x ...\n",
	       params->win.height);
	regw(val, CCDC_FMT_VERT);

	dev_dbg(ccdc_cfg.dev, "\nWriting 0x%x to FMT_VERT...\n", val);

	dev_dbg(ccdc_cfg.dev, "\nbelow regw(val, FMT_VERT)...");

	/*
	 * Configure Horizontal offset register. If pack 8 is enabled then
	 * 1 pixel will take 1 byte
	 */
	if ((config_params->data_sz == CCDC_DATA_8BITS) ||
	    config_params->alaw.enable)
		regw((params->win.width + CCDC_32BYTE_ALIGN_VAL) &
		    CCDC_HSIZE_OFF_MASK, CCDC_HSIZE_OFF);
	else
		/* else one pixel will take 2 byte */
		regw(((params->win.width * CCDC_TWO_BYTES_PER_PIXEL) +
		    CCDC_32BYTE_ALIGN_VAL) & CCDC_HSIZE_OFF_MASK,
		    CCDC_HSIZE_OFF);

	/* Set value for SDOFST */
	if (params->frm_fmt == CCDC_FRMFMT_INTERLACED) {
		if (params->image_invert_enable) {
			/* For intelace inverse mode */
			regw(CCDC_INTERLACED_IMAGE_INVERT, CCDC_SDOFST);
			dev_dbg(ccdc_cfg.dev, "\nWriting 0x4B6D to SDOFST..\n");
		}

		else {
			/* For intelace non inverse mode */
			regw(CCDC_INTERLACED_NO_IMAGE_INVERT, CCDC_SDOFST);
			dev_dbg(ccdc_cfg.dev, "\nWriting 0x0249 to SDOFST..\n");
		}
	} else if (params->frm_fmt == CCDC_FRMFMT_PROGRESSIVE) {
		regw(CCDC_PROGRESSIVE_NO_IMAGE_INVERT, CCDC_SDOFST);
		dev_dbg(ccdc_cfg.dev, "\nWriting 0x0000 to SDOFST...\n");
	}

	/*
	 * Configure video port pixel selection (VPOUT)
	 * Here -1 is to make the height value less than FMT_VERT.FMTLNV
	 */
	if (params->frm_fmt == CCDC_FRMFMT_PROGRESSIVE)
		val = (((params->win.height - 1) & CCDC_VP_OUT_VERT_NUM_MASK))
		    << CCDC_VP_OUT_VERT_NUM_SHIFT;
	else
		val =
		    ((((params->win.height >> CCDC_INTERLACED_HEIGHT_SHIFT) -
		     1) & CCDC_VP_OUT_VERT_NUM_MASK)) <<
		    CCDC_VP_OUT_VERT_NUM_SHIFT;

	val |= ((((params->win.width))) & CCDC_VP_OUT_HORZ_NUM_MASK)
	    << CCDC_VP_OUT_HORZ_NUM_SHIFT;
	val |= (params->win.left) & CCDC_VP_OUT_HORZ_ST_MASK;
	regw(val, CCDC_VP_OUT);

	dev_dbg(ccdc_cfg.dev, "\nWriting 0x%x to VP_OUT...\n", val);
	regw(syn_mode, CCDC_SYN_MODE);
	dev_dbg(ccdc_cfg.dev, "\nWriting 0x%x to SYN_MODE...\n", syn_mode);

	ccdc_sbl_reset();
	dev_dbg(ccdc_cfg.dev, "\nend of ccdc_config_raw...");
	ccdc_readregs();
}