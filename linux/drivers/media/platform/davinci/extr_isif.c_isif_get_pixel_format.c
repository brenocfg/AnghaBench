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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_9__ {scalar_t__ pix_order; } ;
struct TYPE_6__ {scalar_t__ alg; } ;
struct TYPE_7__ {TYPE_1__ compress; } ;
struct TYPE_8__ {TYPE_2__ config_params; } ;
struct TYPE_10__ {scalar_t__ if_type; TYPE_4__ ycbcr; TYPE_3__ bayer; } ;

/* Variables and functions */
 scalar_t__ CCDC_PIXORDER_YCBYCR ; 
 scalar_t__ ISIF_ALAW ; 
 scalar_t__ ISIF_DPCM ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_SBGGR16 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_SBGGR8 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_UYVY ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_YUYV ; 
 scalar_t__ VPFE_RAW_BAYER ; 
 TYPE_5__ isif_cfg ; 

__attribute__((used)) static u32 isif_get_pixel_format(void)
{
	u32 pixfmt;

	if (isif_cfg.if_type == VPFE_RAW_BAYER)
		if (isif_cfg.bayer.config_params.compress.alg == ISIF_ALAW ||
		    isif_cfg.bayer.config_params.compress.alg == ISIF_DPCM)
			pixfmt = V4L2_PIX_FMT_SBGGR8;
		else
			pixfmt = V4L2_PIX_FMT_SBGGR16;
	else {
		if (isif_cfg.ycbcr.pix_order == CCDC_PIXORDER_YCBYCR)
			pixfmt = V4L2_PIX_FMT_YUYV;
		else
			pixfmt = V4L2_PIX_FMT_UYVY;
	}
	return pixfmt;
}