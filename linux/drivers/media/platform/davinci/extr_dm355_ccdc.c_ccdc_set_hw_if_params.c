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
struct vpfe_hw_if_param {int if_type; int /*<<< orphan*/  hdpol; int /*<<< orphan*/  vdpol; } ;
struct TYPE_3__ {int /*<<< orphan*/  hd_pol; int /*<<< orphan*/  vd_pol; } ;
struct TYPE_4__ {int if_type; TYPE_1__ ycbcr; } ;

/* Variables and functions */
 int EINVAL ; 
#define  VPFE_BT656 130 
#define  VPFE_YCBCR_SYNC_16 129 
#define  VPFE_YCBCR_SYNC_8 128 
 TYPE_2__ ccdc_cfg ; 

__attribute__((used)) static int ccdc_set_hw_if_params(struct vpfe_hw_if_param *params)
{
	ccdc_cfg.if_type = params->if_type;

	switch (params->if_type) {
	case VPFE_BT656:
	case VPFE_YCBCR_SYNC_16:
	case VPFE_YCBCR_SYNC_8:
		ccdc_cfg.ycbcr.vd_pol = params->vdpol;
		ccdc_cfg.ycbcr.hd_pol = params->hdpol;
		break;
	default:
		/* TODO add support for raw bayer here */
		return -EINVAL;
	}
	return 0;
}