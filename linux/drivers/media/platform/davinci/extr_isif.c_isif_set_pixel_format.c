#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  pix_order; } ;
struct TYPE_6__ {scalar_t__ alg; } ;
struct TYPE_7__ {TYPE_1__ compress; } ;
struct TYPE_8__ {int /*<<< orphan*/  pix_fmt; TYPE_2__ config_params; } ;
struct TYPE_10__ {scalar_t__ if_type; void* data_pack; TYPE_4__ ycbcr; TYPE_3__ bayer; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCDC_PIXFMT_RAW ; 
 int /*<<< orphan*/  CCDC_PIXORDER_CBYCRY ; 
 int /*<<< orphan*/  CCDC_PIXORDER_YCBYCR ; 
 int EINVAL ; 
 scalar_t__ ISIF_ALAW ; 
 scalar_t__ ISIF_DPCM ; 
 scalar_t__ ISIF_NO_COMPRESSION ; 
 void* ISIF_PACK_16BIT ; 
 void* ISIF_PACK_8BIT ; 
 unsigned int V4L2_PIX_FMT_SBGGR16 ; 
 unsigned int V4L2_PIX_FMT_SBGGR8 ; 
 unsigned int V4L2_PIX_FMT_UYVY ; 
 unsigned int V4L2_PIX_FMT_YUYV ; 
 scalar_t__ VPFE_RAW_BAYER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 TYPE_5__ isif_cfg ; 

__attribute__((used)) static int isif_set_pixel_format(unsigned int pixfmt)
{
	if (isif_cfg.if_type == VPFE_RAW_BAYER) {
		if (pixfmt == V4L2_PIX_FMT_SBGGR8) {
			if ((isif_cfg.bayer.config_params.compress.alg !=
			     ISIF_ALAW) &&
			    (isif_cfg.bayer.config_params.compress.alg !=
			     ISIF_DPCM)) {
				dev_dbg(isif_cfg.dev,
					"Either configure A-Law or DPCM\n");
				return -EINVAL;
			}
			isif_cfg.data_pack = ISIF_PACK_8BIT;
		} else if (pixfmt == V4L2_PIX_FMT_SBGGR16) {
			isif_cfg.bayer.config_params.compress.alg =
					ISIF_NO_COMPRESSION;
			isif_cfg.data_pack = ISIF_PACK_16BIT;
		} else
			return -EINVAL;
		isif_cfg.bayer.pix_fmt = CCDC_PIXFMT_RAW;
	} else {
		if (pixfmt == V4L2_PIX_FMT_YUYV)
			isif_cfg.ycbcr.pix_order = CCDC_PIXORDER_YCBYCR;
		else if (pixfmt == V4L2_PIX_FMT_UYVY)
			isif_cfg.ycbcr.pix_order = CCDC_PIXORDER_CBYCRY;
		else
			return -EINVAL;
		isif_cfg.data_pack = ISIF_PACK_8BIT;
	}
	return 0;
}