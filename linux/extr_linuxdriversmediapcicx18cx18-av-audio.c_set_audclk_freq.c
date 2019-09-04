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
typedef  int u32 ;
struct cx18_av_state {scalar_t__ aud_input; int audclk_freq; } ;
struct cx18 {struct cx18_av_state av_state; } ;

/* Variables and functions */
 scalar_t__ CX18_AV_AUDIO_SERIAL2 ; 
 int EINVAL ; 
 int /*<<< orphan*/  cx18_av_write (struct cx18*,int,int) ; 
 int /*<<< orphan*/  cx18_av_write4 (struct cx18*,int,int) ; 

__attribute__((used)) static int set_audclk_freq(struct cx18 *cx, u32 freq)
{
	struct cx18_av_state *state = &cx->av_state;

	if (freq != 32000 && freq != 44100 && freq != 48000)
		return -EINVAL;

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
	 * Below I aim to run the PLLs' VCOs near 400 MHz to minimze error.
	 *
	 * Many thanks to Jeff Campbell and Mike Bradley for their extensive
	 * investigation, experimentation, testing, and suggested solutions of
	 * of audio/video sync problems with SVideo and CVBS captures.
	 */

	if (state->aud_input > CX18_AV_AUDIO_SERIAL2) {
		switch (freq) {
		case 32000:
			/*
			 * VID_PLL Integer = 0x0f, VID_PLL Post Divider = 0x04
			 * AUX_PLL Integer = 0x0d, AUX PLL Post Divider = 0x20
			 */
			cx18_av_write4(cx, 0x108, 0x200d040f);

			/* VID_PLL Fraction = 0x2be2fe */
			/* xtal * 0xf.15f17f0/4 = 108 MHz: 432 MHz pre-postdiv*/
			cx18_av_write4(cx, 0x10c, 0x002be2fe);

			/* AUX_PLL Fraction = 0x176740c */
			/* xtal * 0xd.bb3a060/0x20 = 32000 * 384: 393 MHz p-pd*/
			cx18_av_write4(cx, 0x110, 0x0176740c);

			/* src3/4/6_ctl */
			/* 0x1.f77f = (4 * xtal/8*2/455) / 32000 */
			cx18_av_write4(cx, 0x900, 0x0801f77f);
			cx18_av_write4(cx, 0x904, 0x0801f77f);
			cx18_av_write4(cx, 0x90c, 0x0801f77f);

			/* SA_MCLK_SEL=1, SA_MCLK_DIV=0x20 */
			cx18_av_write(cx, 0x127, 0x60);

			/* AUD_COUNT = 0x2fff = 8 samples * 4 * 384 - 1 */
			cx18_av_write4(cx, 0x12c, 0x11202fff);

			/*
			 * EN_AV_LOCK = 0
			 * VID_COUNT = 0x0d2ef8 = 107999.000 * 8 =
			 *  ((8 samples/32,000) * (13,500,000 * 8) * 4 - 1) * 8
			 */
			cx18_av_write4(cx, 0x128, 0xa00d2ef8);
			break;

		case 44100:
			/*
			 * VID_PLL Integer = 0x0f, VID_PLL Post Divider = 0x04
			 * AUX_PLL Integer = 0x0e, AUX PLL Post Divider = 0x18
			 */
			cx18_av_write4(cx, 0x108, 0x180e040f);

			/* VID_PLL Fraction = 0x2be2fe */
			/* xtal * 0xf.15f17f0/4 = 108 MHz: 432 MHz pre-postdiv*/
			cx18_av_write4(cx, 0x10c, 0x002be2fe);

			/* AUX_PLL Fraction = 0x062a1f2 */
			/* xtal * 0xe.3150f90/0x18 = 44100 * 384: 406 MHz p-pd*/
			cx18_av_write4(cx, 0x110, 0x0062a1f2);

			/* src3/4/6_ctl */
			/* 0x1.6d59 = (4 * xtal/8*2/455) / 44100 */
			cx18_av_write4(cx, 0x900, 0x08016d59);
			cx18_av_write4(cx, 0x904, 0x08016d59);
			cx18_av_write4(cx, 0x90c, 0x08016d59);

			/* SA_MCLK_SEL=1, SA_MCLK_DIV=0x18 */
			cx18_av_write(cx, 0x127, 0x58);

			/* AUD_COUNT = 0x92ff = 49 samples * 2 * 384 - 1 */
			cx18_av_write4(cx, 0x12c, 0x112092ff);

			/*
			 * EN_AV_LOCK = 0
			 * VID_COUNT = 0x1d4bf8 = 239999.000 * 8 =
			 *  ((49 samples/44,100) * (13,500,000 * 8) * 2 - 1) * 8
			 */
			cx18_av_write4(cx, 0x128, 0xa01d4bf8);
			break;

		case 48000:
			/*
			 * VID_PLL Integer = 0x0f, VID_PLL Post Divider = 0x04
			 * AUX_PLL Integer = 0x0e, AUX PLL Post Divider = 0x16
			 */
			cx18_av_write4(cx, 0x108, 0x160e040f);

			/* VID_PLL Fraction = 0x2be2fe */
			/* xtal * 0xf.15f17f0/4 = 108 MHz: 432 MHz pre-postdiv*/
			cx18_av_write4(cx, 0x10c, 0x002be2fe);

			/* AUX_PLL Fraction = 0x05227ad */
			/* xtal * 0xe.2913d68/0x16 = 48000 * 384: 406 MHz p-pd*/
			cx18_av_write4(cx, 0x110, 0x005227ad);

			/* src3/4/6_ctl */
			/* 0x1.4faa = (4 * xtal/8*2/455) / 48000 */
			cx18_av_write4(cx, 0x900, 0x08014faa);
			cx18_av_write4(cx, 0x904, 0x08014faa);
			cx18_av_write4(cx, 0x90c, 0x08014faa);

			/* SA_MCLK_SEL=1, SA_MCLK_DIV=0x16 */
			cx18_av_write(cx, 0x127, 0x56);

			/* AUD_COUNT = 0x5fff = 4 samples * 16 * 384 - 1 */
			cx18_av_write4(cx, 0x12c, 0x11205fff);

			/*
			 * EN_AV_LOCK = 0
			 * VID_COUNT = 0x1193f8 = 143999.000 * 8 =
			 *  ((4 samples/48,000) * (13,500,000 * 8) * 16 - 1) * 8
			 */
			cx18_av_write4(cx, 0x128, 0xa01193f8);
			break;
		}
	} else {
		switch (freq) {
		case 32000:
			/*
			 * VID_PLL Integer = 0x0f, VID_PLL Post Divider = 0x04
			 * AUX_PLL Integer = 0x0d, AUX PLL Post Divider = 0x30
			 */
			cx18_av_write4(cx, 0x108, 0x300d040f);

			/* VID_PLL Fraction = 0x2be2fe */
			/* xtal * 0xf.15f17f0/4 = 108 MHz: 432 MHz pre-postdiv*/
			cx18_av_write4(cx, 0x10c, 0x002be2fe);

			/* AUX_PLL Fraction = 0x176740c */
			/* xtal * 0xd.bb3a060/0x30 = 32000 * 256: 393 MHz p-pd*/
			cx18_av_write4(cx, 0x110, 0x0176740c);

			/* src1_ctl */
			/* 0x1.0000 = 32000/32000 */
			cx18_av_write4(cx, 0x8f8, 0x08010000);

			/* src3/4/6_ctl */
			/* 0x2.0000 = 2 * (32000/32000) */
			cx18_av_write4(cx, 0x900, 0x08020000);
			cx18_av_write4(cx, 0x904, 0x08020000);
			cx18_av_write4(cx, 0x90c, 0x08020000);

			/* SA_MCLK_SEL=1, SA_MCLK_DIV=0x30 */
			cx18_av_write(cx, 0x127, 0x70);

			/* AUD_COUNT = 0x1fff = 8 samples * 4 * 256 - 1 */
			cx18_av_write4(cx, 0x12c, 0x11201fff);

			/*
			 * EN_AV_LOCK = 0
			 * VID_COUNT = 0x0d2ef8 = 107999.000 * 8 =
			 *  ((8 samples/32,000) * (13,500,000 * 8) * 4 - 1) * 8
			 */
			cx18_av_write4(cx, 0x128, 0xa00d2ef8);
			break;

		case 44100:
			/*
			 * VID_PLL Integer = 0x0f, VID_PLL Post Divider = 0x04
			 * AUX_PLL Integer = 0x0e, AUX PLL Post Divider = 0x24
			 */
			cx18_av_write4(cx, 0x108, 0x240e040f);

			/* VID_PLL Fraction = 0x2be2fe */
			/* xtal * 0xf.15f17f0/4 = 108 MHz: 432 MHz pre-postdiv*/
			cx18_av_write4(cx, 0x10c, 0x002be2fe);

			/* AUX_PLL Fraction = 0x062a1f2 */
			/* xtal * 0xe.3150f90/0x24 = 44100 * 256: 406 MHz p-pd*/
			cx18_av_write4(cx, 0x110, 0x0062a1f2);

			/* src1_ctl */
			/* 0x1.60cd = 44100/32000 */
			cx18_av_write4(cx, 0x8f8, 0x080160cd);

			/* src3/4/6_ctl */
			/* 0x1.7385 = 2 * (32000/44100) */
			cx18_av_write4(cx, 0x900, 0x08017385);
			cx18_av_write4(cx, 0x904, 0x08017385);
			cx18_av_write4(cx, 0x90c, 0x08017385);

			/* SA_MCLK_SEL=1, SA_MCLK_DIV=0x24 */
			cx18_av_write(cx, 0x127, 0x64);

			/* AUD_COUNT = 0x61ff = 49 samples * 2 * 256 - 1 */
			cx18_av_write4(cx, 0x12c, 0x112061ff);

			/*
			 * EN_AV_LOCK = 0
			 * VID_COUNT = 0x1d4bf8 = 239999.000 * 8 =
			 *  ((49 samples/44,100) * (13,500,000 * 8) * 2 - 1) * 8
			 */
			cx18_av_write4(cx, 0x128, 0xa01d4bf8);
			break;

		case 48000:
			/*
			 * VID_PLL Integer = 0x0f, VID_PLL Post Divider = 0x04
			 * AUX_PLL Integer = 0x0d, AUX PLL Post Divider = 0x20
			 */
			cx18_av_write4(cx, 0x108, 0x200d040f);

			/* VID_PLL Fraction = 0x2be2fe */
			/* xtal * 0xf.15f17f0/4 = 108 MHz: 432 MHz pre-postdiv*/
			cx18_av_write4(cx, 0x10c, 0x002be2fe);

			/* AUX_PLL Fraction = 0x176740c */
			/* xtal * 0xd.bb3a060/0x20 = 48000 * 256: 393 MHz p-pd*/
			cx18_av_write4(cx, 0x110, 0x0176740c);

			/* src1_ctl */
			/* 0x1.8000 = 48000/32000 */
			cx18_av_write4(cx, 0x8f8, 0x08018000);

			/* src3/4/6_ctl */
			/* 0x1.5555 = 2 * (32000/48000) */
			cx18_av_write4(cx, 0x900, 0x08015555);
			cx18_av_write4(cx, 0x904, 0x08015555);
			cx18_av_write4(cx, 0x90c, 0x08015555);

			/* SA_MCLK_SEL=1, SA_MCLK_DIV=0x20 */
			cx18_av_write(cx, 0x127, 0x60);

			/* AUD_COUNT = 0x3fff = 4 samples * 16 * 256 - 1 */
			cx18_av_write4(cx, 0x12c, 0x11203fff);

			/*
			 * EN_AV_LOCK = 0
			 * VID_COUNT = 0x1193f8 = 143999.000 * 8 =
			 *  ((4 samples/48,000) * (13,500,000 * 8) * 16 - 1) * 8
			 */
			cx18_av_write4(cx, 0x128, 0xa01193f8);
			break;
		}
	}

	state->audclk_freq = freq;

	return 0;
}