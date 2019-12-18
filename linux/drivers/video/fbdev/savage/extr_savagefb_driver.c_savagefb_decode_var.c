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
typedef  int /*<<< orphan*/  timings ;
struct xtimings {int Clock; int dblscan; int interlaced; int HDisplay; int HSyncStart; int HSyncEnd; int HTotal; int VDisplay; int VSyncStart; int VSyncEnd; int VTotal; int /*<<< orphan*/  sync; } ;
struct savagefb_par {int depth; int vwidth; scalar_t__ chip; scalar_t__ MCLK; } ;
struct savage_reg {int CR67; unsigned char CR3A; int CR53; int CR31; int CR66; int CR58; int SR15; int SR18; int CR43; int CR45; int CR65; int CR40; int MMPR0; int MMPR1; int MMPR2; int MMPR3; int SR10; int SR11; unsigned int SR12; unsigned int SR13; unsigned int SR29; int CR42; int CR34; int* CRTC; int CR3B; int CR3C; int CR5D; int CR5E; int CR91; int CR51; int CR90; int MiscOutReg; int CR50; int CR33; int CR36; int CR68; int CR6F; int CR86; int CR88; int CRB0; scalar_t__ CR69; } ;
struct fb_var_screeninfo {unsigned int pixclock; int vmode; int xres; int right_margin; int hsync_len; int left_margin; int yres; int lower_margin; int vsync_len; int upper_margin; int bits_per_pixel; int xres_virtual; int /*<<< orphan*/  sync; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int FB_VMODE_DOUBLE ; 
 int FB_VMODE_INTERLACED ; 
 scalar_t__ S3_SAVAGE2000 ; 
 scalar_t__ S3_SAVAGE3D ; 
 int /*<<< orphan*/  S3_SAVAGE_MOBILE_SERIES (scalar_t__) ; 
 int /*<<< orphan*/  SavageCalcClock (int,int,int,int,int /*<<< orphan*/ ,int,int,int,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  common_calc_clock (scalar_t__,int,int,int,int /*<<< orphan*/ ,int,int,int,int*,int*) ; 
 int /*<<< orphan*/  memset (struct xtimings*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vgaHWInit (struct fb_var_screeninfo*,struct savagefb_par*,struct xtimings*,struct savage_reg*) ; 
 int vga_in8 (int,struct savagefb_par*) ; 
 int /*<<< orphan*/  vga_out8 (int,int,struct savagefb_par*) ; 

__attribute__((used)) static int savagefb_decode_var(struct fb_var_screeninfo   *var,
			       struct savagefb_par        *par,
			       struct savage_reg          *reg)
{
	struct xtimings timings;
	int width, dclk, i, j; /*, refresh; */
	unsigned int m, n, r;
	unsigned char tmp = 0;
	unsigned int pixclock = var->pixclock;

	DBG("savagefb_decode_var");

	memset(&timings, 0, sizeof(timings));

	if (!pixclock) pixclock = 10000;	/* 10ns = 100MHz */
	timings.Clock = 1000000000 / pixclock;
	if (timings.Clock < 1) timings.Clock = 1;
	timings.dblscan = var->vmode & FB_VMODE_DOUBLE;
	timings.interlaced = var->vmode & FB_VMODE_INTERLACED;
	timings.HDisplay = var->xres;
	timings.HSyncStart = timings.HDisplay + var->right_margin;
	timings.HSyncEnd = timings.HSyncStart + var->hsync_len;
	timings.HTotal = timings.HSyncEnd + var->left_margin;
	timings.VDisplay = var->yres;
	timings.VSyncStart = timings.VDisplay + var->lower_margin;
	timings.VSyncEnd = timings.VSyncStart + var->vsync_len;
	timings.VTotal = timings.VSyncEnd + var->upper_margin;
	timings.sync = var->sync;


	par->depth  = var->bits_per_pixel;
	par->vwidth = var->xres_virtual;

	if (var->bits_per_pixel == 16  &&  par->chip == S3_SAVAGE3D) {
		timings.HDisplay *= 2;
		timings.HSyncStart *= 2;
		timings.HSyncEnd *= 2;
		timings.HTotal *= 2;
	}

	/*
	 * This will allocate the datastructure and initialize all of the
	 * generic VGA registers.
	 */
	vgaHWInit(var, par, &timings, reg);

	/* We need to set CR67 whether or not we use the BIOS. */

	dclk = timings.Clock;
	reg->CR67 = 0x00;

	switch(var->bits_per_pixel) {
	case 8:
		if ((par->chip == S3_SAVAGE2000) && (dclk >= 230000))
			reg->CR67 = 0x10;	/* 8bpp, 2 pixels/clock */
		else
			reg->CR67 = 0x00;	/* 8bpp, 1 pixel/clock */
		break;
	case 15:
		if (S3_SAVAGE_MOBILE_SERIES(par->chip) ||
		    ((par->chip == S3_SAVAGE2000) && (dclk >= 230000)))
			reg->CR67 = 0x30;	/* 15bpp, 2 pixel/clock */
		else
			reg->CR67 = 0x20;	/* 15bpp, 1 pixels/clock */
		break;
	case 16:
		if (S3_SAVAGE_MOBILE_SERIES(par->chip) ||
		   ((par->chip == S3_SAVAGE2000) && (dclk >= 230000)))
			reg->CR67 = 0x50;	/* 16bpp, 2 pixel/clock */
		else
			reg->CR67 = 0x40;	/* 16bpp, 1 pixels/clock */
		break;
	case 24:
		reg->CR67 = 0x70;
		break;
	case 32:
		reg->CR67 = 0xd0;
		break;
	}

	/*
	 * Either BIOS use is disabled, or we failed to find a suitable
	 * match.  Fall back to traditional register-crunching.
	 */

	vga_out8(0x3d4, 0x3a, par);
	tmp = vga_in8(0x3d5, par);
	if (1 /*FIXME:psav->pci_burst*/)
		reg->CR3A = (tmp & 0x7f) | 0x15;
	else
		reg->CR3A = tmp | 0x95;

	reg->CR53 = 0x00;
	reg->CR31 = 0x8c;
	reg->CR66 = 0x89;

	vga_out8(0x3d4, 0x58, par);
	reg->CR58 = vga_in8(0x3d5, par) & 0x80;
	reg->CR58 |= 0x13;

	reg->SR15 = 0x03 | 0x80;
	reg->SR18 = 0x00;
	reg->CR43 = reg->CR45 = reg->CR65 = 0x00;

	vga_out8(0x3d4, 0x40, par);
	reg->CR40 = vga_in8(0x3d5, par) & ~0x01;

	reg->MMPR0 = 0x010400;
	reg->MMPR1 = 0x00;
	reg->MMPR2 = 0x0808;
	reg->MMPR3 = 0x08080810;

	SavageCalcClock(dclk, 1, 1, 127, 0, 4, 180000, 360000, &m, &n, &r);
	/* m = 107; n = 4; r = 2; */

	if (par->MCLK <= 0) {
		reg->SR10 = 255;
		reg->SR11 = 255;
	} else {
		common_calc_clock(par->MCLK, 1, 1, 31, 0, 3, 135000, 270000,
				   &reg->SR11, &reg->SR10);
		/*      reg->SR10 = 80; // MCLK == 286000 */
		/*      reg->SR11 = 125; */
	}

	reg->SR12 = (r << 6) | (n & 0x3f);
	reg->SR13 = m & 0xff;
	reg->SR29 = (r & 4) | (m & 0x100) >> 5 | (n & 0x40) >> 2;

	if (var->bits_per_pixel < 24)
		reg->MMPR0 -= 0x8000;
	else
		reg->MMPR0 -= 0x4000;

	if (timings.interlaced)
		reg->CR42 = 0x20;
	else
		reg->CR42 = 0x00;

	reg->CR34 = 0x10; /* display fifo */

	i = ((((timings.HTotal >> 3) - 5) & 0x100) >> 8) |
		((((timings.HDisplay >> 3) - 1) & 0x100) >> 7) |
		((((timings.HSyncStart >> 3) - 1) & 0x100) >> 6) |
		((timings.HSyncStart & 0x800) >> 7);

	if ((timings.HSyncEnd >> 3) - (timings.HSyncStart >> 3) > 64)
		i |= 0x08;
	if ((timings.HSyncEnd >> 3) - (timings.HSyncStart >> 3) > 32)
		i |= 0x20;

	j = (reg->CRTC[0] + ((i & 0x01) << 8) +
	     reg->CRTC[4] + ((i & 0x10) << 4) + 1) / 2;

	if (j - (reg->CRTC[4] + ((i & 0x10) << 4)) < 4) {
		if (reg->CRTC[4] + ((i & 0x10) << 4) + 4 <=
		    reg->CRTC[0] + ((i & 0x01) << 8))
			j = reg->CRTC[4] + ((i & 0x10) << 4) + 4;
		else
			j = reg->CRTC[0] + ((i & 0x01) << 8) + 1;
	}

	reg->CR3B = j & 0xff;
	i |= (j & 0x100) >> 2;
	reg->CR3C = (reg->CRTC[0] + ((i & 0x01) << 8)) / 2;
	reg->CR5D = i;
	reg->CR5E = (((timings.VTotal - 2) & 0x400) >> 10) |
		(((timings.VDisplay - 1) & 0x400) >> 9) |
		(((timings.VSyncStart) & 0x400) >> 8) |
		(((timings.VSyncStart) & 0x400) >> 6) | 0x40;
	width = (var->xres_virtual * ((var->bits_per_pixel+7) / 8)) >> 3;
	reg->CR91 = reg->CRTC[19] = 0xff & width;
	reg->CR51 = (0x300 & width) >> 4;
	reg->CR90 = 0x80 | (width >> 8);
	reg->MiscOutReg |= 0x0c;

	/* Set frame buffer description. */

	if (var->bits_per_pixel <= 8)
		reg->CR50 = 0;
	else if (var->bits_per_pixel <= 16)
		reg->CR50 = 0x10;
	else
		reg->CR50 = 0x30;

	if (var->xres_virtual <= 640)
		reg->CR50 |= 0x40;
	else if (var->xres_virtual == 800)
		reg->CR50 |= 0x80;
	else if (var->xres_virtual == 1024)
		reg->CR50 |= 0x00;
	else if (var->xres_virtual == 1152)
		reg->CR50 |= 0x01;
	else if (var->xres_virtual == 1280)
		reg->CR50 |= 0xc0;
	else if (var->xres_virtual == 1600)
		reg->CR50 |= 0x81;
	else
		reg->CR50 |= 0xc1;	/* Use GBD */

	if (par->chip == S3_SAVAGE2000)
		reg->CR33 = 0x08;
	else
		reg->CR33 = 0x20;

	reg->CRTC[0x17] = 0xeb;

	reg->CR67 |= 1;

	vga_out8(0x3d4, 0x36, par);
	reg->CR36 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x68, par);
	reg->CR68 = vga_in8(0x3d5, par);
	reg->CR69 = 0;
	vga_out8(0x3d4, 0x6f, par);
	reg->CR6F = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x86, par);
	reg->CR86 = vga_in8(0x3d5, par);
	vga_out8(0x3d4, 0x88, par);
	reg->CR88 = vga_in8(0x3d5, par) | 0x08;
	vga_out8(0x3d4, 0xb0, par);
	reg->CRB0 = vga_in8(0x3d5, par) | 0x80;

	return 0;
}