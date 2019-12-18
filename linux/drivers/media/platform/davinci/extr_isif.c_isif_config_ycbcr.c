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
struct isif_ycbcr_config {int pix_fmt; int frm_fmt; int fid_pol; int hd_pol; int vd_pol; int pix_order; scalar_t__ buf_type; TYPE_1__ win; } ;
struct TYPE_4__ {int if_type; int /*<<< orphan*/  dev; struct isif_ycbcr_config ycbcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCDCFG ; 
 scalar_t__ CCDC_BUFTYPE_FLD_INTERLEAVED ; 
 int CCDC_FRMFMT_INTERLACED ; 
 int CCDC_PIXFMT_YCBCR_16BIT ; 
 int CCDC_PIXFMT_YCBCR_8BIT ; 
 int EINVAL ; 
 int /*<<< orphan*/  HSIZE ; 
 int ISIF_BW656_ENABLE ; 
 int ISIF_DATA_PACK8 ; 
 int ISIF_FID_POL_SHIFT ; 
 int ISIF_FRM_FMT_SHIFT ; 
 int ISIF_HD_POL_SHIFT ; 
 int ISIF_INPUT_SHIFT ; 
 int ISIF_PIX_ORDER_SHIFT ; 
 int ISIF_VD_POL_SHIFT ; 
 int ISIF_YCINSWP_YCBCR ; 
 int /*<<< orphan*/  MODESET ; 
 int /*<<< orphan*/  REC656IF ; 
 int /*<<< orphan*/  SDOFST ; 
#define  VPFE_BT1120 132 
#define  VPFE_BT656 131 
#define  VPFE_BT656_10BIT 130 
 int VPFE_PINPOL_NEGATIVE ; 
#define  VPFE_YCBCR_SYNC_16 129 
#define  VPFE_YCBCR_SYNC_8 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ isif_cfg ; 
 int /*<<< orphan*/  isif_setwin (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  regw (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isif_config_ycbcr(void)
{
	struct isif_ycbcr_config *params = &isif_cfg.ycbcr;
	u32 modeset = 0, ccdcfg = 0;

	dev_dbg(isif_cfg.dev, "\nStarting isif_config_ycbcr...");

	/* configure pixel format or input mode */
	modeset = modeset | (params->pix_fmt << ISIF_INPUT_SHIFT) |
		  (params->frm_fmt << ISIF_FRM_FMT_SHIFT) |
		  (params->fid_pol << ISIF_FID_POL_SHIFT) |
		  (params->hd_pol << ISIF_HD_POL_SHIFT) |
		  (params->vd_pol << ISIF_VD_POL_SHIFT);

	/* pack the data to 8-bit ISIFCFG */
	switch (isif_cfg.if_type) {
	case VPFE_BT656:
		if (params->pix_fmt != CCDC_PIXFMT_YCBCR_8BIT) {
			dev_dbg(isif_cfg.dev, "Invalid pix_fmt(input mode)\n");
			return -EINVAL;
		}
		modeset |= (VPFE_PINPOL_NEGATIVE << ISIF_VD_POL_SHIFT);
		regw(3, REC656IF);
		ccdcfg = ccdcfg | ISIF_DATA_PACK8 | ISIF_YCINSWP_YCBCR;
		break;
	case VPFE_BT656_10BIT:
		if (params->pix_fmt != CCDC_PIXFMT_YCBCR_8BIT) {
			dev_dbg(isif_cfg.dev, "Invalid pix_fmt(input mode)\n");
			return -EINVAL;
		}
		/* setup BT.656, embedded sync  */
		regw(3, REC656IF);
		/* enable 10 bit mode in ccdcfg */
		ccdcfg = ccdcfg | ISIF_DATA_PACK8 | ISIF_YCINSWP_YCBCR |
			ISIF_BW656_ENABLE;
		break;
	case VPFE_BT1120:
		if (params->pix_fmt != CCDC_PIXFMT_YCBCR_16BIT) {
			dev_dbg(isif_cfg.dev, "Invalid pix_fmt(input mode)\n");
			return -EINVAL;
		}
		regw(3, REC656IF);
		break;

	case VPFE_YCBCR_SYNC_8:
		ccdcfg |= ISIF_DATA_PACK8;
		ccdcfg |= ISIF_YCINSWP_YCBCR;
		if (params->pix_fmt != CCDC_PIXFMT_YCBCR_8BIT) {
			dev_dbg(isif_cfg.dev, "Invalid pix_fmt(input mode)\n");
			return -EINVAL;
		}
		break;
	case VPFE_YCBCR_SYNC_16:
		if (params->pix_fmt != CCDC_PIXFMT_YCBCR_16BIT) {
			dev_dbg(isif_cfg.dev, "Invalid pix_fmt(input mode)\n");
			return -EINVAL;
		}
		break;
	default:
		/* should never come here */
		dev_dbg(isif_cfg.dev, "Invalid interface type\n");
		return -EINVAL;
	}

	regw(modeset, MODESET);

	/* Set up pix order */
	ccdcfg |= params->pix_order << ISIF_PIX_ORDER_SHIFT;

	regw(ccdcfg, CCDCFG);

	/* configure video window */
	if ((isif_cfg.if_type == VPFE_BT1120) ||
	    (isif_cfg.if_type == VPFE_YCBCR_SYNC_16))
		isif_setwin(&params->win, params->frm_fmt, 1);
	else
		isif_setwin(&params->win, params->frm_fmt, 2);

	/*
	 * configure the horizontal line offset
	 * this is done by rounding up width to a multiple of 16 pixels
	 * and multiply by two to account for y:cb:cr 4:2:2 data
	 */
	regw(((((params->win.width * 2) + 31) & 0xffffffe0) >> 5), HSIZE);

	/* configure the memory line offset */
	if ((params->frm_fmt == CCDC_FRMFMT_INTERLACED) &&
	    (params->buf_type == CCDC_BUFTYPE_FLD_INTERLEAVED))
		/* two fields are interleaved in memory */
		regw(0x00000249, SDOFST);

	return 0;
}