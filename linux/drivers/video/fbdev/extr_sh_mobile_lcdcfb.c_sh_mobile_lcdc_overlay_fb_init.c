#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sh_mobile_lcdc_priv {int /*<<< orphan*/  dev; } ;
struct sh_mobile_lcdc_overlay {int index; TYPE_2__* format; int /*<<< orphan*/  yres_virtual; int /*<<< orphan*/  xres_virtual; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; int /*<<< orphan*/  pitch; int /*<<< orphan*/  fb_size; int /*<<< orphan*/  dma_handle; int /*<<< orphan*/  fb_mem; struct fb_info* info; TYPE_1__* channel; } ;
struct fb_var_screeninfo {int grayscale; int /*<<< orphan*/  bits_per_pixel; int /*<<< orphan*/  activate; int /*<<< orphan*/  yres_virtual; int /*<<< orphan*/  xres_virtual; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; } ;
struct TYPE_6__ {int ypanstep; int xpanstep; int /*<<< orphan*/  visual; int /*<<< orphan*/  line_length; int /*<<< orphan*/  smem_len; int /*<<< orphan*/  smem_start; int /*<<< orphan*/  id; } ;
struct fb_info {struct fb_var_screeninfo var; TYPE_3__ fix; struct sh_mobile_lcdc_overlay* par; int /*<<< orphan*/  screen_base; int /*<<< orphan*/  device; int /*<<< orphan*/ * fbops; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int fourcc; int /*<<< orphan*/  bpp; scalar_t__ yuv; } ;
struct TYPE_4__ {struct sh_mobile_lcdc_priv* lcdc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FBINFO_FLAG_DEFAULT ; 
 int /*<<< orphan*/  FB_ACTIVATE_NOW ; 
 int /*<<< orphan*/  FB_VISUAL_FOURCC ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 
#define  V4L2_PIX_FMT_NV12 131 
#define  V4L2_PIX_FMT_NV16 130 
#define  V4L2_PIX_FMT_NV21 129 
#define  V4L2_PIX_FMT_NV61 128 
 struct fb_info* framebuffer_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fb_var_screeninfo*,int /*<<< orphan*/ ,int) ; 
 int sh_mobile_lcdc_overlay_check_var (struct fb_var_screeninfo*,struct fb_info*) ; 
 TYPE_3__ sh_mobile_lcdc_overlay_fix ; 
 int /*<<< orphan*/  sh_mobile_lcdc_overlay_ops ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 

__attribute__((used)) static int
sh_mobile_lcdc_overlay_fb_init(struct sh_mobile_lcdc_overlay *ovl)
{
	struct sh_mobile_lcdc_priv *priv = ovl->channel->lcdc;
	struct fb_var_screeninfo *var;
	struct fb_info *info;

	/* Allocate and initialize the frame buffer device. */
	info = framebuffer_alloc(0, priv->dev);
	if (!info)
		return -ENOMEM;

	ovl->info = info;

	info->flags = FBINFO_FLAG_DEFAULT;
	info->fbops = &sh_mobile_lcdc_overlay_ops;
	info->device = priv->dev;
	info->screen_base = ovl->fb_mem;
	info->par = ovl;

	/* Initialize fixed screen information. Restrict pan to 2 lines steps
	 * for NV12 and NV21.
	 */
	info->fix = sh_mobile_lcdc_overlay_fix;
	snprintf(info->fix.id, sizeof(info->fix.id),
		 "SH Mobile LCDC Overlay %u", ovl->index);
	info->fix.smem_start = ovl->dma_handle;
	info->fix.smem_len = ovl->fb_size;
	info->fix.line_length = ovl->pitch;

	if (ovl->format->yuv)
		info->fix.visual = FB_VISUAL_FOURCC;
	else
		info->fix.visual = FB_VISUAL_TRUECOLOR;

	switch (ovl->format->fourcc) {
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
		info->fix.ypanstep = 2;
		/* Fall through */
	case V4L2_PIX_FMT_NV16:
	case V4L2_PIX_FMT_NV61:
		info->fix.xpanstep = 2;
	}

	/* Initialize variable screen information. */
	var = &info->var;
	memset(var, 0, sizeof(*var));
	var->xres = ovl->xres;
	var->yres = ovl->yres;
	var->xres_virtual = ovl->xres_virtual;
	var->yres_virtual = ovl->yres_virtual;
	var->activate = FB_ACTIVATE_NOW;

	/* Use the legacy API by default for RGB formats, and the FOURCC API
	 * for YUV formats.
	 */
	if (!ovl->format->yuv)
		var->bits_per_pixel = ovl->format->bpp;
	else
		var->grayscale = ovl->format->fourcc;

	return sh_mobile_lcdc_overlay_check_var(var, info);
}