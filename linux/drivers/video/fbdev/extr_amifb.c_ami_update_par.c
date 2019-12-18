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
struct TYPE_2__ {scalar_t__ smem_start; } ;
struct fb_info {TYPE_1__ fix; struct amifb_par* par; } ;
struct amifb_par {short clk_shift; int vmode; short xoffset; short diwstrt_h; short xres; short next_line; short ddfstrt; short ddfstop; short bpl2mod; int bplcon0; int fmode; short bpl1mod; int yoffset; int vyres; int yres; int diwstrt_v; scalar_t__ bplpt0; scalar_t__ bplpt0wrap; int /*<<< orphan*/  bplcon1; } ;

/* Variables and functions */
 int BPC0_LACE ; 
 int FB_VMODE_SMOOTH_XPAN ; 
 int FB_VMODE_YWRAP ; 
 int FMODE_BSCAN2 ; 
 scalar_t__ IS_AGA ; 
 short div8 (short) ; 
 short downx (short,short) ; 
 int /*<<< orphan*/  hscroll2hw (short) ; 
 int maxfmode ; 
 short min_fstrt ; 
 scalar_t__ mod2 (int) ; 
 short modx (short,short) ; 
 short up64 (short) ; 
 short upx (short,short) ; 

__attribute__((used)) static void ami_update_par(struct fb_info *info)
{
	struct amifb_par *par = info->par;
	short clk_shift, vshift, fstrt, fsize, fstop, fconst,  shift, move, mod;

	clk_shift = par->clk_shift;

	if (!(par->vmode & FB_VMODE_SMOOTH_XPAN))
		par->xoffset = upx(16 << maxfmode, par->xoffset);

	fconst = 16 << maxfmode << clk_shift;
	vshift = modx(16 << maxfmode, par->xoffset);
	fstrt = par->diwstrt_h - (vshift << clk_shift) - 4;
	fsize = (par->xres + vshift) << clk_shift;
	shift = modx(fconst, fstrt);
	move = downx(2 << maxfmode, div8(par->xoffset));
	if (maxfmode + clk_shift > 1) {
		fstrt = downx(fconst, fstrt) - 64;
		fsize = upx(fconst, fsize);
		fstop = fstrt + fsize - fconst;
	} else {
		mod = fstrt = downx(fconst, fstrt) - fconst;
		fstop = fstrt + upx(fconst, fsize) - 64;
		fsize = up64(fsize);
		fstrt = fstop - fsize + 64;
		if (fstrt < min_fstrt) {
			fstop += min_fstrt - fstrt;
			fstrt = min_fstrt;
		}
		move = move - div8((mod - fstrt)>>clk_shift);
	}
	mod = par->next_line - div8(fsize>>clk_shift);
	par->ddfstrt = fstrt;
	par->ddfstop = fstop;
	par->bplcon1 = hscroll2hw(shift);
	par->bpl2mod = mod;
	if (par->bplcon0 & BPC0_LACE)
		par->bpl2mod += par->next_line;
	if (IS_AGA && (par->fmode & FMODE_BSCAN2))
		par->bpl1mod = -div8(fsize>>clk_shift);
	else
		par->bpl1mod = par->bpl2mod;

	if (par->yoffset) {
		par->bplpt0 = info->fix.smem_start +
			      par->next_line * par->yoffset + move;
		if (par->vmode & FB_VMODE_YWRAP) {
			if (par->yoffset > par->vyres - par->yres) {
				par->bplpt0wrap = info->fix.smem_start + move;
				if (par->bplcon0 & BPC0_LACE &&
				    mod2(par->diwstrt_v + par->vyres -
					 par->yoffset))
					par->bplpt0wrap += par->next_line;
			}
		}
	} else
		par->bplpt0 = info->fix.smem_start + move;

	if (par->bplcon0 & BPC0_LACE && mod2(par->diwstrt_v))
		par->bplpt0 += par->next_line;
}