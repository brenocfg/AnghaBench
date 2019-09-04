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
struct cx18 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXADEC_AUX_PLL_FRAC ; 
 int /*<<< orphan*/  CXADEC_I2S_MCLK ; 
 int /*<<< orphan*/  CXADEC_PLL_CTRL1 ; 
 int /*<<< orphan*/  CXADEC_VID_PLL_FRAC ; 
 int /*<<< orphan*/  cx18_av_write (struct cx18*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx18_av_write4 (struct cx18*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cx18_av_init(struct cx18 *cx)
{
	/*
	 * The crystal freq used in calculations in this driver will be
	 * 28.636360 MHz.
	 * Aim to run the PLLs' VCOs near 400 MHz to minimze errors.
	 */

	/*
	 * VDCLK  Integer = 0x0f, Post Divider = 0x04
	 * AIMCLK Integer = 0x0e, Post Divider = 0x16
	 */
	cx18_av_write4(cx, CXADEC_PLL_CTRL1, 0x160e040f);

	/* VDCLK Fraction = 0x2be2fe */
	/* xtal * 0xf.15f17f0/4 = 108 MHz: 432 MHz before post divide */
	cx18_av_write4(cx, CXADEC_VID_PLL_FRAC, 0x002be2fe);

	/* AIMCLK Fraction = 0x05227ad */
	/* xtal * 0xe.2913d68/0x16 = 48000 * 384: 406 MHz pre post-div*/
	cx18_av_write4(cx, CXADEC_AUX_PLL_FRAC, 0x005227ad);

	/* SA_MCLK_SEL=1, SA_MCLK_DIV=0x16 */
	cx18_av_write(cx, CXADEC_I2S_MCLK, 0x56);
}