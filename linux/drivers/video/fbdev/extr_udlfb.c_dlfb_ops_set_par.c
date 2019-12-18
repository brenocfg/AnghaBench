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
typedef  int u32 ;
typedef  int u16 ;
struct fb_var_screeninfo {int xres; int bits_per_pixel; int yres; int /*<<< orphan*/  vmode; scalar_t__ activate; } ;
struct TYPE_2__ {int line_length; int smem_len; } ;
struct fb_info {struct fb_var_screeninfo var; TYPE_1__ fix; scalar_t__ screen_base; struct dlfb_data* par; } ;
struct dlfb_data {scalar_t__ fb_count; struct fb_var_screeninfo current_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_VMODE_SMOOTH_XPAN ; 
 int /*<<< orphan*/  dlfb_handle_damage (struct dlfb_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int dlfb_realloc_framebuffer (struct dlfb_data*,struct fb_info*,int) ; 
 int dlfb_set_video_mode (struct dlfb_data*,struct fb_var_screeninfo*) ; 
 int /*<<< orphan*/  memcmp (struct fb_var_screeninfo*,struct fb_var_screeninfo*,int) ; 

__attribute__((used)) static int dlfb_ops_set_par(struct fb_info *info)
{
	struct dlfb_data *dlfb = info->par;
	int result;
	u16 *pix_framebuffer;
	int i;
	struct fb_var_screeninfo fvs;
	u32 line_length = info->var.xres * (info->var.bits_per_pixel / 8);

	/* clear the activate field because it causes spurious miscompares */
	fvs = info->var;
	fvs.activate = 0;
	fvs.vmode &= ~FB_VMODE_SMOOTH_XPAN;

	if (!memcmp(&dlfb->current_mode, &fvs, sizeof(struct fb_var_screeninfo)))
		return 0;

	result = dlfb_realloc_framebuffer(dlfb, info, info->var.yres * line_length);
	if (result)
		return result;

	result = dlfb_set_video_mode(dlfb, &info->var);

	if (result)
		return result;

	dlfb->current_mode = fvs;
	info->fix.line_length = line_length;

	if (dlfb->fb_count == 0) {

		/* paint greenscreen */

		pix_framebuffer = (u16 *) info->screen_base;
		for (i = 0; i < info->fix.smem_len / 2; i++)
			pix_framebuffer[i] = 0x37e6;
	}

	dlfb_handle_damage(dlfb, 0, 0, info->var.xres, info->var.yres);

	return 0;
}