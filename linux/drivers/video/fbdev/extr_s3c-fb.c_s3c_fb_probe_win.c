#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct s3c_fb_win_variant {int palette_sz; scalar_t__ palette_16bpp; } ;
struct TYPE_12__ {int length; scalar_t__ offset; } ;
struct TYPE_11__ {int offset; int length; } ;
struct TYPE_10__ {int offset; int length; } ;
struct TYPE_13__ {TYPE_5__ b; TYPE_4__ g; TYPE_3__ r; } ;
struct s3c_fb_win {unsigned int index; struct s3c_fb_win_variant variant; int /*<<< orphan*/  pseudo_palette; TYPE_6__ palette; int /*<<< orphan*/ * palette_buffer; struct s3c_fb_pd_win* windata; struct s3c_fb* parent; struct fb_info* fbinfo; } ;
struct s3c_fb_pd_win {scalar_t__ max_bpp; scalar_t__ xres; scalar_t__ yres; int /*<<< orphan*/  default_bpp; } ;
struct TYPE_8__ {int /*<<< orphan*/  wait; } ;
struct s3c_fb {int /*<<< orphan*/  dev; TYPE_2__* pdata; TYPE_1__ vsync_info; } ;
struct fb_videomode {scalar_t__ xres; scalar_t__ yres; } ;
struct fb_var_screeninfo {int /*<<< orphan*/  bits_per_pixel; int /*<<< orphan*/  vmode; int /*<<< orphan*/  activate; } ;
struct TYPE_14__ {int /*<<< orphan*/  id; int /*<<< orphan*/  accel; int /*<<< orphan*/  type; } ;
struct fb_info {TYPE_7__ fix; int /*<<< orphan*/  cmap; struct fb_var_screeninfo var; int /*<<< orphan*/ * pseudo_palette; int /*<<< orphan*/  flags; int /*<<< orphan*/ * fbops; struct s3c_fb_win* par; } ;
struct TYPE_9__ {struct fb_videomode* vtiming; struct s3c_fb_pd_win** win; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FBINFO_FLAG_DEFAULT ; 
 int /*<<< orphan*/  FB_ACCEL_NONE ; 
 int /*<<< orphan*/  FB_ACTIVATE_NOW ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VMODE_NONINTERLACED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int fb_alloc_cmap (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  fb_set_cmap (int /*<<< orphan*/ *,struct fb_info*) ; 
 int /*<<< orphan*/  fb_videomode_to_var (struct fb_var_screeninfo*,struct fb_videomode*) ; 
 struct fb_info* framebuffer_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int register_framebuffer (struct fb_info*) ; 
 int s3c_fb_alloc_memory (struct s3c_fb*,struct s3c_fb_win*) ; 
 int s3c_fb_check_var (struct fb_var_screeninfo*,struct fb_info*) ; 
 int /*<<< orphan*/  s3c_fb_ops ; 
 int /*<<< orphan*/  s3c_fb_set_par (struct fb_info*) ; 

__attribute__((used)) static int s3c_fb_probe_win(struct s3c_fb *sfb, unsigned int win_no,
			    struct s3c_fb_win_variant *variant,
			    struct s3c_fb_win **res)
{
	struct fb_var_screeninfo *var;
	struct fb_videomode initmode;
	struct s3c_fb_pd_win *windata;
	struct s3c_fb_win *win;
	struct fb_info *fbinfo;
	int palette_size;
	int ret;

	dev_dbg(sfb->dev, "probing window %d, variant %p\n", win_no, variant);

	init_waitqueue_head(&sfb->vsync_info.wait);

	palette_size = variant->palette_sz * 4;

	fbinfo = framebuffer_alloc(sizeof(struct s3c_fb_win) +
				   palette_size * sizeof(u32), sfb->dev);
	if (!fbinfo)
		return -ENOMEM;

	windata = sfb->pdata->win[win_no];
	initmode = *sfb->pdata->vtiming;

	WARN_ON(windata->max_bpp == 0);
	WARN_ON(windata->xres == 0);
	WARN_ON(windata->yres == 0);

	win = fbinfo->par;
	*res = win;
	var = &fbinfo->var;
	win->variant = *variant;
	win->fbinfo = fbinfo;
	win->parent = sfb;
	win->windata = windata;
	win->index = win_no;
	win->palette_buffer = (u32 *)(win + 1);

	ret = s3c_fb_alloc_memory(sfb, win);
	if (ret) {
		dev_err(sfb->dev, "failed to allocate display memory\n");
		return ret;
	}

	/* setup the r/b/g positions for the window's palette */
	if (win->variant.palette_16bpp) {
		/* Set RGB 5:6:5 as default */
		win->palette.r.offset = 11;
		win->palette.r.length = 5;
		win->palette.g.offset = 5;
		win->palette.g.length = 6;
		win->palette.b.offset = 0;
		win->palette.b.length = 5;

	} else {
		/* Set 8bpp or 8bpp and 1bit alpha */
		win->palette.r.offset = 16;
		win->palette.r.length = 8;
		win->palette.g.offset = 8;
		win->palette.g.length = 8;
		win->palette.b.offset = 0;
		win->palette.b.length = 8;
	}

	/* setup the initial video mode from the window */
	initmode.xres = windata->xres;
	initmode.yres = windata->yres;
	fb_videomode_to_var(&fbinfo->var, &initmode);

	fbinfo->fix.type	= FB_TYPE_PACKED_PIXELS;
	fbinfo->fix.accel	= FB_ACCEL_NONE;
	fbinfo->var.activate	= FB_ACTIVATE_NOW;
	fbinfo->var.vmode	= FB_VMODE_NONINTERLACED;
	fbinfo->var.bits_per_pixel = windata->default_bpp;
	fbinfo->fbops		= &s3c_fb_ops;
	fbinfo->flags		= FBINFO_FLAG_DEFAULT;
	fbinfo->pseudo_palette  = &win->pseudo_palette;

	/* prepare to actually start the framebuffer */

	ret = s3c_fb_check_var(&fbinfo->var, fbinfo);
	if (ret < 0) {
		dev_err(sfb->dev, "check_var failed on initial video params\n");
		return ret;
	}

	/* create initial colour map */

	ret = fb_alloc_cmap(&fbinfo->cmap, win->variant.palette_sz, 1);
	if (ret == 0)
		fb_set_cmap(&fbinfo->cmap, fbinfo);
	else
		dev_err(sfb->dev, "failed to allocate fb cmap\n");

	s3c_fb_set_par(fbinfo);

	dev_dbg(sfb->dev, "about to register framebuffer\n");

	/* run the check_var and set_par on our configuration. */

	ret = register_framebuffer(fbinfo);
	if (ret < 0) {
		dev_err(sfb->dev, "failed to register framebuffer\n");
		return ret;
	}

	dev_info(sfb->dev, "window %d: fb %s\n", win_no, fbinfo->fix.id);

	return 0;
}