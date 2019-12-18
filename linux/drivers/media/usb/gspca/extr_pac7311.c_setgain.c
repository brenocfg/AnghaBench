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
struct gspca_dev {TYPE_1__* gain; } ;
typedef  int s32 ;
struct TYPE_2__ {int maximum; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void setgain(struct gspca_dev *gspca_dev, s32 val)
{
	reg_w(gspca_dev, 0xff, 0x04);			/* page 4 */
	reg_w(gspca_dev, 0x0e, 0x00);
	reg_w(gspca_dev, 0x0f, gspca_dev->gain->maximum - val + 1);

	/* load registers to sensor (Bit 0, auto clear) */
	reg_w(gspca_dev, 0x11, 0x01);
}