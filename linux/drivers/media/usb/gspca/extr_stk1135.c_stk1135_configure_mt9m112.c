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
typedef  int u16 ;
struct sensor_val {int member_0; int member_1; int reg; int val; } ;
struct TYPE_2__ {int width; int height; } ;
struct gspca_dev {TYPE_1__ pixfmt; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct sensor_val const*) ; 
 int /*<<< orphan*/  sensor_write (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void stk1135_configure_mt9m112(struct gspca_dev *gspca_dev)
{
	static const struct sensor_val cfg[] = {
		/* restart&reset, chip enable, reserved */
		{ 0x00d, 0x000b }, { 0x00d, 0x0008 }, { 0x035, 0x0022 },
		/* mode ctl: AWB on, AE both, clip aper corr, defect corr, AE */
		{ 0x106, 0x700e },

		{ 0x2dd, 0x18e0 }, /* B-R thresholds, */

		/* AWB */
		{ 0x21f, 0x0180 }, /* Cb and Cr limits */
		{ 0x220, 0xc814 }, { 0x221, 0x8080 }, /* lum limits, RGB gain */
		{ 0x222, 0xa078 }, { 0x223, 0xa078 }, /* R, B limit */
		{ 0x224, 0x5f20 }, { 0x228, 0xea02 }, /* mtx adj lim, adv ctl */
		{ 0x229, 0x867a }, /* wide gates */

		/* Color correction */
		/* imager gains base, delta, delta signs */
		{ 0x25e, 0x594c }, { 0x25f, 0x4d51 }, { 0x260, 0x0002 },
		/* AWB adv ctl 2, gain offs */
		{ 0x2ef, 0x0008 }, { 0x2f2, 0x0000 },
		/* base matrix signs, scale K1-5, K6-9 */
		{ 0x202, 0x00ee }, { 0x203, 0x3923 }, { 0x204, 0x0724 },
		/* base matrix coef */
		{ 0x209, 0x00cd }, { 0x20a, 0x0093 }, { 0x20b, 0x0004 },/*K1-3*/
		{ 0x20c, 0x005c }, { 0x20d, 0x00d9 }, { 0x20e, 0x0053 },/*K4-6*/
		{ 0x20f, 0x0008 }, { 0x210, 0x0091 }, { 0x211, 0x00cf },/*K7-9*/
		{ 0x215, 0x0000 }, /* delta mtx signs */
		/* delta matrix coef */
		{ 0x216, 0x0000 }, { 0x217, 0x0000 }, { 0x218, 0x0000 },/*D1-3*/
		{ 0x219, 0x0000 }, { 0x21a, 0x0000 }, { 0x21b, 0x0000 },/*D4-6*/
		{ 0x21c, 0x0000 }, { 0x21d, 0x0000 }, { 0x21e, 0x0000 },/*D7-9*/
		/* enable & disable manual WB to apply color corr. settings */
		{ 0x106, 0xf00e }, { 0x106, 0x700e },

		/* Lens shading correction */
		{ 0x180, 0x0007 }, /* control */
		/* vertical knee 0, 2+1, 4+3 */
		{ 0x181, 0xde13 }, { 0x182, 0xebe2 }, { 0x183, 0x00f6 }, /* R */
		{ 0x184, 0xe114 }, { 0x185, 0xeadd }, { 0x186, 0xfdf6 }, /* G */
		{ 0x187, 0xe511 }, { 0x188, 0xede6 }, { 0x189, 0xfbf7 }, /* B */
		/* horizontal knee 0, 2+1, 4+3, 5 */
		{ 0x18a, 0xd613 }, { 0x18b, 0xedec }, /* R .. */
		{ 0x18c, 0xf9f2 }, { 0x18d, 0x0000 }, /* .. R */
		{ 0x18e, 0xd815 }, { 0x18f, 0xe9ea }, /* G .. */
		{ 0x190, 0xf9f1 }, { 0x191, 0x0002 }, /* .. G */
		{ 0x192, 0xde10 }, { 0x193, 0xefef }, /* B .. */
		{ 0x194, 0xfbf4 }, { 0x195, 0x0002 }, /* .. B */
		/* vertical knee 6+5, 8+7 */
		{ 0x1b6, 0x0e06 }, { 0x1b7, 0x2713 }, /* R */
		{ 0x1b8, 0x1106 }, { 0x1b9, 0x2713 }, /* G */
		{ 0x1ba, 0x0c03 }, { 0x1bb, 0x2a0f }, /* B */
		/* horizontal knee 7+6, 9+8, 10 */
		{ 0x1bc, 0x1208 }, { 0x1bd, 0x1a16 }, { 0x1be, 0x0022 }, /* R */
		{ 0x1bf, 0x150a }, { 0x1c0, 0x1c1a }, { 0x1c1, 0x002d }, /* G */
		{ 0x1c2, 0x1109 }, { 0x1c3, 0x1414 }, { 0x1c4, 0x002a }, /* B */
		{ 0x106, 0x740e }, /* enable lens shading correction */

		/* Gamma correction - context A */
		{ 0x153, 0x0b03 }, { 0x154, 0x4722 }, { 0x155, 0xac82 },
		{ 0x156, 0xdac7 }, { 0x157, 0xf5e9 }, { 0x158, 0xff00 },
		/* Gamma correction - context B */
		{ 0x1dc, 0x0b03 }, { 0x1dd, 0x4722 }, { 0x1de, 0xac82 },
		{ 0x1df, 0xdac7 }, { 0x1e0, 0xf5e9 }, { 0x1e1, 0xff00 },

		/* output format: RGB, invert output pixclock, output bayer */
		{ 0x13a, 0x4300 }, { 0x19b, 0x4300 }, /* for context A, B */
		{ 0x108, 0x0180 }, /* format control - enable bayer row flip */

		{ 0x22f, 0xd100 }, { 0x29c, 0xd100 }, /* AE A, B */

		/* default prg conf, prg ctl - by 0x2d2, prg advance - PA1 */
		{ 0x2d2, 0x0000 }, { 0x2cc, 0x0004 }, { 0x2cb, 0x0001 },

		{ 0x22e, 0x0c3c }, { 0x267, 0x1010 }, /* AE tgt ctl, gain lim */

		/* PLL */
		{ 0x065, 0xa000 }, /* clk ctl - enable PLL (clear bit 14) */
		{ 0x066, 0x2003 }, { 0x067, 0x0501 }, /* PLL M=128, N=3, P=1 */
		{ 0x065, 0x2000 }, /* disable PLL bypass (clear bit 15) */

		{ 0x005, 0x01b8 }, { 0x007, 0x00d8 }, /* horiz blanking B, A */

		/* AE line size, shutter delay limit */
		{ 0x239, 0x06c0 }, { 0x23b, 0x040e }, /* for context A */
		{ 0x23a, 0x06c0 }, { 0x23c, 0x0564 }, /* for context B */
		/* shutter width basis 60Hz, 50Hz */
		{ 0x257, 0x0208 }, { 0x258, 0x0271 }, /* for context A */
		{ 0x259, 0x0209 }, { 0x25a, 0x0271 }, /* for context B */

		{ 0x25c, 0x120d }, { 0x25d, 0x1712 }, /* flicker 60Hz, 50Hz */
		{ 0x264, 0x5e1c }, /* reserved */
		/* flicker, AE gain limits, gain zone limits */
		{ 0x25b, 0x0003 }, { 0x236, 0x7810 }, { 0x237, 0x8304 },

		{ 0x008, 0x0021 }, /* vert blanking A */
	};
	int i;
	u16 width, height;

	for (i = 0; i < ARRAY_SIZE(cfg); i++)
		sensor_write(gspca_dev, cfg[i].reg, cfg[i].val);

	/* set output size */
	width = gspca_dev->pixfmt.width;
	height = gspca_dev->pixfmt.height;
	if (width <= 640 && height <= 512) { /* context A (half readout speed)*/
		sensor_write(gspca_dev, 0x1a7, width);
		sensor_write(gspca_dev, 0x1aa, height);
		/* set read mode context A */
		sensor_write(gspca_dev, 0x0c8, 0x0000);
		/* set resize, read mode, vblank, hblank context A */
		sensor_write(gspca_dev, 0x2c8, 0x0000);
	} else { /* context B (full readout speed) */
		sensor_write(gspca_dev, 0x1a1, width);
		sensor_write(gspca_dev, 0x1a4, height);
		/* set read mode context B */
		sensor_write(gspca_dev, 0x0c8, 0x0008);
		/* set resize, read mode, vblank, hblank context B */
		sensor_write(gspca_dev, 0x2c8, 0x040b);
	}
}