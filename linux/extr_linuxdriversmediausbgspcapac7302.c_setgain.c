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
typedef  int u8 ;
struct gspca_dev {TYPE_1__* gain; } ;
struct TYPE_2__ {int val; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void setgain(struct gspca_dev *gspca_dev)
{
	u8 reg10, reg12;

	if (gspca_dev->gain->val < 32) {
		reg10 = gspca_dev->gain->val;
		reg12 = 0;
	} else {
		reg10 = 31;
		reg12 = gspca_dev->gain->val - 31;
	}

	reg_w(gspca_dev, 0xff, 0x03);			/* page 3 */
	reg_w(gspca_dev, 0x10, reg10);
	reg_w(gspca_dev, 0x12, reg12);

	/* load registers to sensor (Bit 0, auto clear) */
	reg_w(gspca_dev, 0x11, 0x01);
}