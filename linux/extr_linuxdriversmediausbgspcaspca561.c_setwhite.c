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
struct sd {scalar_t__ chip_revision; } ;
struct gspca_dev {int dummy; } ;
typedef  int s32 ;
typedef  int __u8 ;
typedef  int __u16 ;

/* Variables and functions */
 scalar_t__ Rev012A ; 
 int /*<<< orphan*/  reg_w_val (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void setwhite(struct gspca_dev *gspca_dev, s32 white, s32 contrast)
{
	struct sd *sd = (struct sd *) gspca_dev;
	__u8 blue, red;
	__u16 reg;

	/* try to emulate MS-win as possible */
	red = 0x20 + white * 3 / 8;
	blue = 0x90 - white * 5 / 8;
	if (sd->chip_revision == Rev012A) {
		reg = 0x8614;
	} else {
		reg = 0x8651;
		red += contrast - 0x20;
		blue += contrast - 0x20;
		reg_w_val(gspca_dev, 0x8652, contrast + 0x20); /* Gr */
		reg_w_val(gspca_dev, 0x8654, contrast + 0x20); /* Gb */
	}
	reg_w_val(gspca_dev, reg, red);
	reg_w_val(gspca_dev, reg + 2, blue);
}