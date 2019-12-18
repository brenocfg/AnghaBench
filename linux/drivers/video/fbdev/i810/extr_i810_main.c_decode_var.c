#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  P; int /*<<< orphan*/  N; int /*<<< orphan*/  M; } ;
struct i810fb_par {int pixconf; int bltcntl; int depth; int blit_bpp; int /*<<< orphan*/  pitch; int /*<<< orphan*/  watermark; TYPE_2__ regs; } ;
struct TYPE_3__ {int length; } ;
struct fb_var_screeninfo {int bits_per_pixel; int /*<<< orphan*/  pixclock; scalar_t__ nonstd; TYPE_1__ green; int /*<<< orphan*/  yres_virtual; int /*<<< orphan*/  xres_virtual; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; } ;

/* Variables and functions */
 int BPP16 ; 
 int BPP24 ; 
 int BPP8 ; 
 int PIXCONF15 ; 
 int PIXCONF16 ; 
 int PIXCONF24 ; 
 int PIXCONF32 ; 
 int PIXCONF8 ; 
 int /*<<< orphan*/  get_line_length (struct i810fb_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i810_calc_dclk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i810_get_watermark (struct fb_var_screeninfo const*,struct i810fb_par*) ; 
 int /*<<< orphan*/  i810fb_encode_registers (struct fb_var_screeninfo const*,struct i810fb_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void decode_var(const struct fb_var_screeninfo *var, 
		       struct i810fb_par *par)
{
	u32 xres, yres, vxres, vyres;

	xres = var->xres;
	yres = var->yres;
	vxres = var->xres_virtual;
	vyres = var->yres_virtual;

	switch (var->bits_per_pixel) {
	case 8:
		par->pixconf = PIXCONF8;
		par->bltcntl = 0;
		par->depth = 1;
		par->blit_bpp = BPP8;
		break;
	case 16:
		if (var->green.length == 5)
			par->pixconf = PIXCONF15;
		else
			par->pixconf = PIXCONF16;
		par->bltcntl = 16;
		par->depth = 2;
		par->blit_bpp = BPP16;
		break;
	case 24:
		par->pixconf = PIXCONF24;
		par->bltcntl = 32;
		par->depth = 3;
		par->blit_bpp = BPP24;
		break;
	case 32:
		par->pixconf = PIXCONF32;
		par->bltcntl = 0;
		par->depth = 4;
		par->blit_bpp = 3 << 24;
		break;
	}
	if (var->nonstd && var->bits_per_pixel != 8)
		par->pixconf |= 1 << 27;

	i810_calc_dclk(var->pixclock, &par->regs.M, 
		       &par->regs.N, &par->regs.P);
	i810fb_encode_registers(var, par, xres, yres);

	par->watermark = i810_get_watermark(var, par);
	par->pitch = get_line_length(par, vxres, var->bits_per_pixel);
}