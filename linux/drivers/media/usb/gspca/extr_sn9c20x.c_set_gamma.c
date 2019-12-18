#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct gspca_dev {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int*,int) ; 

__attribute__((used)) static void set_gamma(struct gspca_dev *gspca_dev, s32 val)
{
	u8 gamma[17];
	u8 gval = val * 0xb8 / 0x100;

	gamma[0] = 0x0a;
	gamma[1] = 0x13 + (gval * (0xcb - 0x13) / 0xb8);
	gamma[2] = 0x25 + (gval * (0xee - 0x25) / 0xb8);
	gamma[3] = 0x37 + (gval * (0xfa - 0x37) / 0xb8);
	gamma[4] = 0x45 + (gval * (0xfc - 0x45) / 0xb8);
	gamma[5] = 0x55 + (gval * (0xfb - 0x55) / 0xb8);
	gamma[6] = 0x65 + (gval * (0xfc - 0x65) / 0xb8);
	gamma[7] = 0x74 + (gval * (0xfd - 0x74) / 0xb8);
	gamma[8] = 0x83 + (gval * (0xfe - 0x83) / 0xb8);
	gamma[9] = 0x92 + (gval * (0xfc - 0x92) / 0xb8);
	gamma[10] = 0xa1 + (gval * (0xfc - 0xa1) / 0xb8);
	gamma[11] = 0xb0 + (gval * (0xfc - 0xb0) / 0xb8);
	gamma[12] = 0xbf + (gval * (0xfb - 0xbf) / 0xb8);
	gamma[13] = 0xce + (gval * (0xfb - 0xce) / 0xb8);
	gamma[14] = 0xdf + (gval * (0xfd - 0xdf) / 0xb8);
	gamma[15] = 0xea + (gval * (0xf9 - 0xea) / 0xb8);
	gamma[16] = 0xf5;

	reg_w(gspca_dev, 0x1190, gamma, 17);
}