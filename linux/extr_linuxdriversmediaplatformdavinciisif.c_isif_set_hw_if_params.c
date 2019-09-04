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
struct vpfe_hw_if_param {int if_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  pix_fmt; } ;
struct TYPE_5__ {void* pix_order; int /*<<< orphan*/  pix_fmt; } ;
struct TYPE_6__ {int if_type; int /*<<< orphan*/  dev; TYPE_1__ bayer; TYPE_2__ ycbcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCDC_PIXFMT_RAW ; 
 int /*<<< orphan*/  CCDC_PIXFMT_YCBCR_16BIT ; 
 int /*<<< orphan*/  CCDC_PIXFMT_YCBCR_8BIT ; 
 void* CCDC_PIXORDER_CBYCRY ; 
 int EINVAL ; 
#define  VPFE_BT1120 133 
#define  VPFE_BT656 132 
#define  VPFE_BT656_10BIT 131 
#define  VPFE_RAW_BAYER 130 
#define  VPFE_YCBCR_SYNC_16 129 
#define  VPFE_YCBCR_SYNC_8 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__ isif_cfg ; 

__attribute__((used)) static int isif_set_hw_if_params(struct vpfe_hw_if_param *params)
{
	isif_cfg.if_type = params->if_type;

	switch (params->if_type) {
	case VPFE_BT656:
	case VPFE_BT656_10BIT:
	case VPFE_YCBCR_SYNC_8:
		isif_cfg.ycbcr.pix_fmt = CCDC_PIXFMT_YCBCR_8BIT;
		isif_cfg.ycbcr.pix_order = CCDC_PIXORDER_CBYCRY;
		break;
	case VPFE_BT1120:
	case VPFE_YCBCR_SYNC_16:
		isif_cfg.ycbcr.pix_fmt = CCDC_PIXFMT_YCBCR_16BIT;
		isif_cfg.ycbcr.pix_order = CCDC_PIXORDER_CBYCRY;
		break;
	case VPFE_RAW_BAYER:
		isif_cfg.bayer.pix_fmt = CCDC_PIXFMT_RAW;
		break;
	default:
		dev_dbg(isif_cfg.dev, "Invalid interface type\n");
		return -EINVAL;
	}

	return 0;
}