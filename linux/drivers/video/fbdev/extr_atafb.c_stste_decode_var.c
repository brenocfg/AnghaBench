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
struct fb_var_screeninfo {int xres; int yres; int bits_per_pixel; int yres_virtual; int sync; int yoffset; } ;
struct TYPE_3__ {int sync; int /*<<< orphan*/  mode; } ;
struct TYPE_4__ {TYPE_1__ st; } ;
struct atafb_par {int yres_virtual; int next_line; scalar_t__ screen_base; TYPE_2__ hw; } ;

/* Variables and functions */
 int EINVAL ; 
 int FB_SYNC_EXT ; 
 int /*<<< orphan*/  ST_HIGH ; 
 int /*<<< orphan*/  ST_LOW ; 
 int /*<<< orphan*/  ST_MID ; 
 scalar_t__ mono_moni ; 
 scalar_t__ screen_base ; 
 int screen_len ; 
 int st_yres ; 
 int sttt_xres ; 

__attribute__((used)) static int stste_decode_var(struct fb_var_screeninfo *var,
			    struct atafb_par *par)
{
	int xres = var->xres;
	int yres = var->yres;
	int bpp = var->bits_per_pixel;
	int linelen;
	int yres_virtual = var->yres_virtual;

	if (mono_moni) {
		if (bpp > 1 || xres > sttt_xres || yres > st_yres)
			return -EINVAL;
		par->hw.st.mode = ST_HIGH;
		xres = sttt_xres;
		yres = st_yres;
		bpp = 1;
	} else {
		if (bpp > 4 || xres > sttt_xres || yres > st_yres)
			return -EINVAL;
		if (bpp > 2) {
			if (xres > sttt_xres / 2 || yres > st_yres / 2)
				return -EINVAL;
			par->hw.st.mode = ST_LOW;
			xres = sttt_xres / 2;
			yres = st_yres / 2;
			bpp = 4;
		} else if (bpp > 1) {
			if (xres > sttt_xres || yres > st_yres / 2)
				return -EINVAL;
			par->hw.st.mode = ST_MID;
			xres = sttt_xres;
			yres = st_yres / 2;
			bpp = 2;
		} else
			return -EINVAL;
	}
	if (yres_virtual <= 0)
		yres_virtual = 0;
	else if (yres_virtual < yres)
		yres_virtual = yres;
	if (var->sync & FB_SYNC_EXT)
		par->hw.st.sync = (par->hw.st.sync & ~1) | 1;
	else
		par->hw.st.sync = (par->hw.st.sync & ~1);
	linelen = xres * bpp / 8;
	if (yres_virtual * linelen > screen_len && screen_len)
		return -EINVAL;
	if (yres * linelen > screen_len && screen_len)
		return -EINVAL;
	if (var->yoffset + yres > yres_virtual && yres_virtual)
		return -EINVAL;
	par->yres_virtual = yres_virtual;
	par->screen_base = screen_base + var->yoffset * linelen;
	par->next_line = linelen;
	return 0;
}