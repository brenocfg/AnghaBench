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
typedef  int u16 ;
struct gspca_dev {TYPE_1__* exposure; } ;
struct TYPE_2__ {int val; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void setexposure(struct gspca_dev *gspca_dev)
{
	u8 clockdiv;
	u16 exposure;

	/*
	 * Register 2 of frame 3 contains the clock divider configuring the
	 * no fps according to the formula: 90 / reg. sd->exposure is the
	 * desired exposure time in 0.5 ms.
	 */
	clockdiv = (90 * gspca_dev->exposure->val + 1999) / 2000;

	/*
	 * Note clockdiv = 3 also works, but when running at 30 fps, depending
	 * on the scene being recorded, the camera switches to another
	 * quantization table for certain JPEG blocks, and we don't know how
	 * to decompress these blocks. So we cap the framerate at 15 fps.
	 */
	if (clockdiv < 6)
		clockdiv = 6;
	else if (clockdiv > 63)
		clockdiv = 63;

	/*
	 * Register 2 MUST be a multiple of 3, except when between 6 and 12?
	 * Always round up, otherwise we cannot get the desired frametime
	 * using the partial frame time exposure control.
	 */
	if (clockdiv < 6 || clockdiv > 12)
		clockdiv = ((clockdiv + 2) / 3) * 3;

	/*
	 * frame exposure time in ms = 1000 * clockdiv / 90    ->
	 * exposure = (sd->exposure / 2) * 448 / (1000 * clockdiv / 90)
	 */
	exposure = (gspca_dev->exposure->val * 45 * 448) / (1000 * clockdiv);
	/* 0 = use full frametime, 448 = no exposure, reverse it */
	exposure = 448 - exposure;

	reg_w(gspca_dev, 0xff, 0x03);			/* page 3 */
	reg_w(gspca_dev, 0x02, clockdiv);
	reg_w(gspca_dev, 0x0e, exposure & 0xff);
	reg_w(gspca_dev, 0x0f, exposure >> 8);

	/* load registers to sensor (Bit 0, auto clear) */
	reg_w(gspca_dev, 0x11, 0x01);
}