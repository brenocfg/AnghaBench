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
struct TYPE_3__ {int width; } ;
struct ccdc_params_ycbcr {int pix_fmt; int frm_fmt; int fid_pol; int hd_pol; int vd_pol; int pix_order; scalar_t__ buf_type; TYPE_1__ win; scalar_t__ bt656_enable; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; struct ccdc_params_ycbcr ycbcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCDCFG ; 
 scalar_t__ CCDC_BUFTYPE_FLD_INTERLEAVED ; 
 int CCDC_CCDCFG_FIDMD_NO_LATCH_VSYNC ; 
 int CCDC_DATA_PACK_ENABLE ; 
 int CCDC_FID_POL_MASK ; 
 int CCDC_FID_POL_SHIFT ; 
 int CCDC_FRM_FMT_MASK ; 
 int CCDC_FRM_FMT_SHIFT ; 
 int CCDC_HD_POL_MASK ; 
 int CCDC_HD_POL_SHIFT ; 
 int CCDC_INPUT_MODE_MASK ; 
 int CCDC_INPUT_MODE_SHIFT ; 
 int CCDC_LATCH_ON_VSYNC_DISABLE ; 
 int CCDC_REC656IF_BT656_EN ; 
 int CCDC_SDOFST_FIELD_INTERLEAVED ; 
 int CCDC_VD_POL_MASK ; 
 int CCDC_VD_POL_NEGATIVE ; 
 int CCDC_VD_POL_SHIFT ; 
 int CCDC_Y8POS_SHIFT ; 
 int /*<<< orphan*/  HSIZE ; 
 int /*<<< orphan*/  MODESET ; 
 int /*<<< orphan*/  REC656IF ; 
 int /*<<< orphan*/  SDOFST ; 
 TYPE_2__ ccdc_cfg ; 
 int /*<<< orphan*/  ccdc_restore_defaults () ; 
 int /*<<< orphan*/  ccdc_setwin (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regw (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccdc_config_ycbcr(void)
{
	struct ccdc_params_ycbcr *params = &ccdc_cfg.ycbcr;
	u32 temp;

	/* first set the CCDC power on defaults values in all registers */
	dev_dbg(ccdc_cfg.dev, "\nStarting ccdc_config_ycbcr...");
	ccdc_restore_defaults();

	/* configure pixel format & video frame format */
	temp = (((params->pix_fmt & CCDC_INPUT_MODE_MASK) <<
		CCDC_INPUT_MODE_SHIFT) |
		((params->frm_fmt & CCDC_FRM_FMT_MASK) <<
		CCDC_FRM_FMT_SHIFT));

	/* setup BT.656 sync mode */
	if (params->bt656_enable) {
		regw(CCDC_REC656IF_BT656_EN, REC656IF);
		/*
		 * configure the FID, VD, HD pin polarity fld,hd pol positive,
		 * vd negative, 8-bit pack mode
		 */
		temp |= CCDC_VD_POL_NEGATIVE;
	} else {		/* y/c external sync mode */
		temp |= (((params->fid_pol & CCDC_FID_POL_MASK) <<
			CCDC_FID_POL_SHIFT) |
			((params->hd_pol & CCDC_HD_POL_MASK) <<
			CCDC_HD_POL_SHIFT) |
			((params->vd_pol & CCDC_VD_POL_MASK) <<
			CCDC_VD_POL_SHIFT));
	}

	/* pack the data to 8-bit */
	temp |= CCDC_DATA_PACK_ENABLE;

	regw(temp, MODESET);

	/* configure video window */
	ccdc_setwin(&params->win, params->frm_fmt, 2);

	/* configure the order of y cb cr in SD-RAM */
	temp = (params->pix_order << CCDC_Y8POS_SHIFT);
	temp |= CCDC_LATCH_ON_VSYNC_DISABLE | CCDC_CCDCFG_FIDMD_NO_LATCH_VSYNC;
	regw(temp, CCDCFG);

	/*
	 * configure the horizontal line offset. This is done by rounding up
	 * width to a multiple of 16 pixels and multiply by two to account for
	 * y:cb:cr 4:2:2 data
	 */
	regw(((params->win.width * 2 + 31) >> 5), HSIZE);

	/* configure the memory line offset */
	if (params->buf_type == CCDC_BUFTYPE_FLD_INTERLEAVED) {
		/* two fields are interleaved in memory */
		regw(CCDC_SDOFST_FIELD_INTERLEAVED, SDOFST);
	}

	dev_dbg(ccdc_cfg.dev, "\nEnd of ccdc_config_ycbcr...\n");
}