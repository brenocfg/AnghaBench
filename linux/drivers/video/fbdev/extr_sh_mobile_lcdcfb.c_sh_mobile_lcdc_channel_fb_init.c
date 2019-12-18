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
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct sh_mobile_lcdc_chan {TYPE_2__* format; int /*<<< orphan*/  yres_virtual; int /*<<< orphan*/  xres_virtual; TYPE_1__ display; int /*<<< orphan*/  pitch; int /*<<< orphan*/  fb_size; int /*<<< orphan*/  dma_handle; int /*<<< orphan*/  pseudo_palette; int /*<<< orphan*/  fb_mem; struct fb_info* info; struct sh_mobile_lcdc_priv* lcdc; } ;
struct fb_videomode {int dummy; } ;
struct fb_var_screeninfo {int grayscale; int /*<<< orphan*/  bits_per_pixel; int /*<<< orphan*/  activate; int /*<<< orphan*/  yres_virtual; int /*<<< orphan*/  xres_virtual; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_6__ {int ypanstep; int xpanstep; int /*<<< orphan*/  visual; int /*<<< orphan*/  line_length; int /*<<< orphan*/  smem_len; int /*<<< orphan*/  smem_start; } ;
struct fb_info {struct fb_var_screeninfo var; TYPE_3__ fix; int /*<<< orphan*/  cmap; int /*<<< orphan*/  modelist; struct sh_mobile_lcdc_chan* par; int /*<<< orphan*/ * pseudo_palette; int /*<<< orphan*/  screen_base; int /*<<< orphan*/  device; int /*<<< orphan*/ * fbops; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int fourcc; int /*<<< orphan*/  bpp; scalar_t__ yuv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FBINFO_FLAG_DEFAULT ; 
 int /*<<< orphan*/  FB_ACTIVATE_NOW ; 
 int /*<<< orphan*/  FB_VISUAL_FOURCC ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  PALETTE_NR ; 
#define  V4L2_PIX_FMT_NV12 131 
#define  V4L2_PIX_FMT_NV16 130 
#define  V4L2_PIX_FMT_NV21 129 
#define  V4L2_PIX_FMT_NV61 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int fb_alloc_cmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_videomode_to_modelist (struct fb_videomode const*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_videomode_to_var (struct fb_var_screeninfo*,struct fb_videomode const*) ; 
 struct fb_info* framebuffer_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sh_mobile_lcdc_check_var (struct fb_var_screeninfo*,struct fb_info*) ; 
 TYPE_3__ sh_mobile_lcdc_fix ; 
 int /*<<< orphan*/  sh_mobile_lcdc_ops ; 

__attribute__((used)) static int
sh_mobile_lcdc_channel_fb_init(struct sh_mobile_lcdc_chan *ch,
			       const struct fb_videomode *modes,
			       unsigned int num_modes)
{
	struct sh_mobile_lcdc_priv *priv = ch->lcdc;
	struct fb_var_screeninfo *var;
	struct fb_info *info;
	int ret;

	/* Allocate and initialize the frame buffer device. Create the modes
	 * list and allocate the color map.
	 */
	info = framebuffer_alloc(0, priv->dev);
	if (!info)
		return -ENOMEM;

	ch->info = info;

	info->flags = FBINFO_FLAG_DEFAULT;
	info->fbops = &sh_mobile_lcdc_ops;
	info->device = priv->dev;
	info->screen_base = ch->fb_mem;
	info->pseudo_palette = &ch->pseudo_palette;
	info->par = ch;

	fb_videomode_to_modelist(modes, num_modes, &info->modelist);

	ret = fb_alloc_cmap(&info->cmap, PALETTE_NR, 0);
	if (ret < 0) {
		dev_err(priv->dev, "unable to allocate cmap\n");
		return ret;
	}

	/* Initialize fixed screen information. Restrict pan to 2 lines steps
	 * for NV12 and NV21.
	 */
	info->fix = sh_mobile_lcdc_fix;
	info->fix.smem_start = ch->dma_handle;
	info->fix.smem_len = ch->fb_size;
	info->fix.line_length = ch->pitch;

	if (ch->format->yuv)
		info->fix.visual = FB_VISUAL_FOURCC;
	else
		info->fix.visual = FB_VISUAL_TRUECOLOR;

	switch (ch->format->fourcc) {
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
		info->fix.ypanstep = 2;
		/* Fall through */
	case V4L2_PIX_FMT_NV16:
	case V4L2_PIX_FMT_NV61:
		info->fix.xpanstep = 2;
	}

	/* Initialize variable screen information using the first mode as
	 * default.
	 */
	var = &info->var;
	fb_videomode_to_var(var, modes);
	var->width = ch->display.width;
	var->height = ch->display.height;
	var->xres_virtual = ch->xres_virtual;
	var->yres_virtual = ch->yres_virtual;
	var->activate = FB_ACTIVATE_NOW;

	/* Use the legacy API by default for RGB formats, and the FOURCC API
	 * for YUV formats.
	 */
	if (!ch->format->yuv)
		var->bits_per_pixel = ch->format->bpp;
	else
		var->grayscale = ch->format->fourcc;

	ret = sh_mobile_lcdc_check_var(var, info);
	if (ret)
		return ret;

	return 0;
}