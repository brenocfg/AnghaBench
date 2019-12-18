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
struct mmpfb_info {scalar_t__ pix_fmt; int /*<<< orphan*/  fb_size; int /*<<< orphan*/  fb_start; int /*<<< orphan*/  pseudo_palette; int /*<<< orphan*/  fb_start_dma; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int xres_virtual; int bits_per_pixel; int /*<<< orphan*/  yres; } ;
struct TYPE_3__ {int line_length; int /*<<< orphan*/  visual; int /*<<< orphan*/  smem_len; int /*<<< orphan*/  smem_start; int /*<<< orphan*/  accel; scalar_t__ ywrapstep; int /*<<< orphan*/  ypanstep; scalar_t__ xpanstep; scalar_t__ type_aux; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct fb_info {int flags; int node; int /*<<< orphan*/  cmap; int /*<<< orphan*/  screen_size; int /*<<< orphan*/  screen_base; int /*<<< orphan*/  pseudo_palette; int /*<<< orphan*/ * fbops; TYPE_2__ var; TYPE_1__ fix; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FBINFO_DEFAULT ; 
 int FBINFO_HWACCEL_XPAN ; 
 int FBINFO_HWACCEL_YPAN ; 
 int FBINFO_PARTIAL_PAN_OK ; 
 int /*<<< orphan*/  FB_ACCEL_NONE ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 
 scalar_t__ PIXFMT_PSEUDOCOLOR ; 
 scalar_t__ fb_alloc_cmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmpfb_ops ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fb_info_setup(struct fb_info *info,
			struct mmpfb_info *fbi)
{
	int ret = 0;
	/* Initialise static fb parameters.*/
	info->flags = FBINFO_DEFAULT | FBINFO_PARTIAL_PAN_OK |
		FBINFO_HWACCEL_XPAN | FBINFO_HWACCEL_YPAN;
	info->node = -1;
	strcpy(info->fix.id, fbi->name);
	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.type_aux = 0;
	info->fix.xpanstep = 0;
	info->fix.ypanstep = info->var.yres;
	info->fix.ywrapstep = 0;
	info->fix.accel = FB_ACCEL_NONE;
	info->fix.smem_start = fbi->fb_start_dma;
	info->fix.smem_len = fbi->fb_size;
	info->fix.visual = (fbi->pix_fmt == PIXFMT_PSEUDOCOLOR) ?
		FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_TRUECOLOR;
	info->fix.line_length = info->var.xres_virtual *
		info->var.bits_per_pixel / 8;
	info->fbops = &mmpfb_ops;
	info->pseudo_palette = fbi->pseudo_palette;
	info->screen_base = fbi->fb_start;
	info->screen_size = fbi->fb_size;

	/* For FB framework: Allocate color map and Register framebuffer*/
	if (fb_alloc_cmap(&info->cmap, 256, 0) < 0)
		ret = -ENOMEM;

	return ret;
}