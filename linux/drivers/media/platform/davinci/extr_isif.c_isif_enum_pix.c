#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ if_type; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 scalar_t__ VPFE_RAW_BAYER ; 
 TYPE_1__ isif_cfg ; 
 int /*<<< orphan*/ * isif_raw_bayer_pix_formats ; 
 int /*<<< orphan*/ * isif_raw_yuv_pix_formats ; 

__attribute__((used)) static int isif_enum_pix(u32 *pix, int i)
{
	int ret = -EINVAL;

	if (isif_cfg.if_type == VPFE_RAW_BAYER) {
		if (i < ARRAY_SIZE(isif_raw_bayer_pix_formats)) {
			*pix = isif_raw_bayer_pix_formats[i];
			ret = 0;
		}
	} else {
		if (i < ARRAY_SIZE(isif_raw_yuv_pix_formats)) {
			*pix = isif_raw_yuv_pix_formats[i];
			ret = 0;
		}
	}

	return ret;
}