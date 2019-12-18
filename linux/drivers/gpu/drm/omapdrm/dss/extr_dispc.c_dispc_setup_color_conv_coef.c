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
struct dispc_device {TYPE_1__* feat; } ;
struct csc_coef_yuv2rgb {int member_0; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; int member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_1; } ;
struct csc_coef_rgb2yuv {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; int member_8; int member_9; } ;
struct TYPE_2__ {scalar_t__ has_writeback; } ;

/* Variables and functions */
 int dispc_get_num_ovls (struct dispc_device*) ; 
 int /*<<< orphan*/  dispc_ovl_write_color_conv_coef (struct dispc_device*,int,struct csc_coef_yuv2rgb const*) ; 
 int /*<<< orphan*/  dispc_wb_write_color_conv_coef (struct dispc_device*,struct csc_coef_rgb2yuv const*) ; 

__attribute__((used)) static void dispc_setup_color_conv_coef(struct dispc_device *dispc)
{
	int i;
	int num_ovl = dispc_get_num_ovls(dispc);

	/* YUV -> RGB, ITU-R BT.601, limited range */
	const struct csc_coef_yuv2rgb coefs_yuv2rgb_bt601_lim = {
		298,    0,  409,	/* ry, rcb, rcr */
		298, -100, -208,	/* gy, gcb, gcr */
		298,  516,    0,	/* by, bcb, bcr */
		false,			/* limited range */
	};

	/* RGB -> YUV, ITU-R BT.601, limited range */
	const struct csc_coef_rgb2yuv coefs_rgb2yuv_bt601_lim = {
		 66, 129,  25,		/* yr,   yg,  yb */
		-38, -74, 112,		/* cbr, cbg, cbb */
		112, -94, -18,		/* crr, crg, crb */
		false,			/* limited range */
	};

	for (i = 1; i < num_ovl; i++)
		dispc_ovl_write_color_conv_coef(dispc, i, &coefs_yuv2rgb_bt601_lim);

	if (dispc->feat->has_writeback)
		dispc_wb_write_color_conv_coef(dispc, &coefs_rgb2yuv_bt601_lim);
}