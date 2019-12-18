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
 int /*<<< orphan*/  CX18_ADEC_CONTROL ; 
 int /*<<< orphan*/  CX18_CLOCK_ENABLE1 ; 
 int /*<<< orphan*/  CX18_CLOCK_ENABLE2 ; 
 int /*<<< orphan*/  CX18_CLOCK_SELECT1 ; 
 int /*<<< orphan*/  CX18_CLOCK_SELECT2 ; 
 int /*<<< orphan*/  CX18_FAST_CLOCK_PLL_ADJUST_BANDWIDTH ; 
 int /*<<< orphan*/  CX18_FAST_CLOCK_PLL_FRAC ; 
 int /*<<< orphan*/  CX18_FAST_CLOCK_PLL_INT ; 
 int /*<<< orphan*/  CX18_FAST_CLOCK_PLL_POST ; 
 int /*<<< orphan*/  CX18_FAST_CLOCK_PLL_PRESCALE ; 
 int /*<<< orphan*/  CX18_HALF_CLOCK_SELECT1 ; 
 int /*<<< orphan*/  CX18_HALF_CLOCK_SELECT2 ; 
 int /*<<< orphan*/  CX18_MPEG_CLOCK_PLL_FRAC ; 
 int /*<<< orphan*/  CX18_MPEG_CLOCK_PLL_INT ; 
 int /*<<< orphan*/  CX18_MPEG_CLOCK_PLL_POST ; 
 int /*<<< orphan*/  CX18_PLL_POWER_DOWN ; 
 int /*<<< orphan*/  CX18_SLOW_CLOCK_PLL_FRAC ; 
 int /*<<< orphan*/  CX18_SLOW_CLOCK_PLL_INT ; 
 int /*<<< orphan*/  CX18_SLOW_CLOCK_PLL_POST ; 
 int /*<<< orphan*/  cx18_write_reg (struct cx18*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx18_write_reg_expect (struct cx18*,int,int /*<<< orphan*/ ,int,int) ; 

void cx18_init_power(struct cx18 *cx, int lowpwr)
{
	/* power-down Spare and AOM PLLs */
	/* power-up fast, slow and mpeg PLLs */
	cx18_write_reg(cx, 0x00000008, CX18_PLL_POWER_DOWN);

	/* ADEC out of sleep */
	cx18_write_reg_expect(cx, 0x00020000, CX18_ADEC_CONTROL,
				  0x00000000, 0x00020002);

	/*
	 * The PLL parameters are based on the external crystal frequency that
	 * would ideally be:
	 *
	 * NTSC Color subcarrier freq * 8 =
	 *	4.5 MHz/286 * 455/2 * 8 = 28.63636363... MHz
	 *
	 * The accidents of history and rationale that explain from where this
	 * combination of magic numbers originate can be found in:
	 *
	 * [1] Abrahams, I. C., "Choice of Chrominance Subcarrier Frequency in
	 * the NTSC Standards", Proceedings of the I-R-E, January 1954, pp 79-80
	 *
	 * [2] Abrahams, I. C., "The 'Frequency Interleaving' Principle in the
	 * NTSC Standards", Proceedings of the I-R-E, January 1954, pp 81-83
	 *
	 * As Mike Bradley has rightly pointed out, it's not the exact crystal
	 * frequency that matters, only that all parts of the driver and
	 * firmware are using the same value (close to the ideal value).
	 *
	 * Since I have a strong suspicion that, if the firmware ever assumes a
	 * crystal value at all, it will assume 28.636360 MHz, the crystal
	 * freq used in calculations in this driver will be:
	 *
	 *	xtal_freq = 28.636360 MHz
	 *
	 * an error of less than 0.13 ppm which is way, way better than any off
	 * the shelf crystal will have for accuracy anyway.
	 *
	 * Below I aim to run the PLLs' VCOs near 400 MHz to minimze errors.
	 *
	 * Many thanks to Jeff Campbell and Mike Bradley for their extensive
	 * investigation, experimentation, testing, and suggested solutions of
	 * of audio/video sync problems with SVideo and CVBS captures.
	 */

	/* the fast clock is at 200/245 MHz */
	/* 1 * xtal_freq * 0x0d.f7df9b8 / 2 = 200 MHz: 400 MHz pre post-divide*/
	/* 1 * xtal_freq * 0x11.1c71eb8 / 2 = 245 MHz: 490 MHz pre post-divide*/
	cx18_write_reg(cx, lowpwr ? 0xD : 0x11, CX18_FAST_CLOCK_PLL_INT);
	cx18_write_reg(cx, lowpwr ? 0x1EFBF37 : 0x038E3D7,
						CX18_FAST_CLOCK_PLL_FRAC);

	cx18_write_reg(cx, 2, CX18_FAST_CLOCK_PLL_POST);
	cx18_write_reg(cx, 1, CX18_FAST_CLOCK_PLL_PRESCALE);
	cx18_write_reg(cx, 4, CX18_FAST_CLOCK_PLL_ADJUST_BANDWIDTH);

	/* set slow clock to 125/120 MHz */
	/* xtal_freq * 0x0d.1861a20 / 3 = 125 MHz: 375 MHz before post-divide */
	/* xtal_freq * 0x0c.92493f8 / 3 = 120 MHz: 360 MHz before post-divide */
	cx18_write_reg(cx, lowpwr ? 0xD : 0xC, CX18_SLOW_CLOCK_PLL_INT);
	cx18_write_reg(cx, lowpwr ? 0x30C344 : 0x124927F,
						CX18_SLOW_CLOCK_PLL_FRAC);
	cx18_write_reg(cx, 3, CX18_SLOW_CLOCK_PLL_POST);

	/* mpeg clock pll 54MHz */
	/* xtal_freq * 0xf.15f17f0 / 8 = 54 MHz: 432 MHz before post-divide */
	cx18_write_reg(cx, 0xF, CX18_MPEG_CLOCK_PLL_INT);
	cx18_write_reg(cx, 0x2BE2FE, CX18_MPEG_CLOCK_PLL_FRAC);
	cx18_write_reg(cx, 8, CX18_MPEG_CLOCK_PLL_POST);

	/* Defaults */
	/* APU = SC or SC/2 = 125/62.5 */
	/* EPU = SC = 125 */
	/* DDR = FC = 180 */
	/* ENC = SC = 125 */
	/* AI1 = SC = 125 */
	/* VIM2 = disabled */
	/* PCI = FC/2 = 90 */
	/* AI2 = disabled */
	/* DEMUX = disabled */
	/* AO = SC/2 = 62.5 */
	/* SER = 54MHz */
	/* VFC = disabled */
	/* USB = disabled */

	if (lowpwr) {
		cx18_write_reg_expect(cx, 0xFFFF0020, CX18_CLOCK_SELECT1,
					  0x00000020, 0xFFFFFFFF);
		cx18_write_reg_expect(cx, 0xFFFF0004, CX18_CLOCK_SELECT2,
					  0x00000004, 0xFFFFFFFF);
	} else {
		/* This doesn't explicitly set every clock select */
		cx18_write_reg_expect(cx, 0x00060004, CX18_CLOCK_SELECT1,
					  0x00000004, 0x00060006);
		cx18_write_reg_expect(cx, 0x00060006, CX18_CLOCK_SELECT2,
					  0x00000006, 0x00060006);
	}

	cx18_write_reg_expect(cx, 0xFFFF0002, CX18_HALF_CLOCK_SELECT1,
				  0x00000002, 0xFFFFFFFF);
	cx18_write_reg_expect(cx, 0xFFFF0104, CX18_HALF_CLOCK_SELECT2,
				  0x00000104, 0xFFFFFFFF);
	cx18_write_reg_expect(cx, 0xFFFF9026, CX18_CLOCK_ENABLE1,
				  0x00009026, 0xFFFFFFFF);
	cx18_write_reg_expect(cx, 0xFFFF3105, CX18_CLOCK_ENABLE2,
				  0x00003105, 0xFFFFFFFF);
}