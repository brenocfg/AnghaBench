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
typedef  int /*<<< orphan*/  u32 ;
struct ccdc_a_law {scalar_t__ enable; } ;
struct TYPE_7__ {scalar_t__ pix_order; } ;
struct TYPE_5__ {struct ccdc_a_law alaw; } ;
struct TYPE_6__ {TYPE_1__ config_params; } ;
struct TYPE_8__ {scalar_t__ if_type; TYPE_3__ ycbcr; TYPE_2__ bayer; } ;

/* Variables and functions */
 scalar_t__ CCDC_PIXORDER_YCBYCR ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_SBGGR16 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_SBGGR8 ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_UYVY ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_YUYV ; 
 scalar_t__ VPFE_RAW_BAYER ; 
 TYPE_4__ ccdc_cfg ; 

__attribute__((used)) static u32 ccdc_get_pixel_format(void)
{
	struct ccdc_a_law *alaw = &ccdc_cfg.bayer.config_params.alaw;
	u32 pixfmt;

	if (ccdc_cfg.if_type == VPFE_RAW_BAYER)
		if (alaw->enable)
			pixfmt = V4L2_PIX_FMT_SBGGR8;
		else
			pixfmt = V4L2_PIX_FMT_SBGGR16;
	else {
		if (ccdc_cfg.ycbcr.pix_order == CCDC_PIXORDER_YCBYCR)
			pixfmt = V4L2_PIX_FMT_YUYV;
		else
			pixfmt = V4L2_PIX_FMT_UYVY;
	}
	return pixfmt;
}