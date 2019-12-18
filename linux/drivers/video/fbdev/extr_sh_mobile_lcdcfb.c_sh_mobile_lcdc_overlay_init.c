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
struct sh_mobile_lcdc_overlay {int enabled; int alpha; int xres; int xres_virtual; int yres; int yres_virtual; int pitch; int fb_size; int /*<<< orphan*/  fb_mem; int /*<<< orphan*/  dma_handle; TYPE_3__* cfg; struct sh_mobile_lcdc_format_info const* format; scalar_t__ pos_y; scalar_t__ pos_x; scalar_t__ rop3; int /*<<< orphan*/  mode; TYPE_2__* channel; } ;
struct sh_mobile_lcdc_format_info {int bpp; int /*<<< orphan*/  yuv; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int max_xres; int max_yres; int /*<<< orphan*/  fourcc; } ;
struct TYPE_5__ {TYPE_1__* lcdc; } ;
struct TYPE_4__ {struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LCDC_OVERLAY_BLEND ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sh_mobile_lcdc_format_info* sh_mobile_format_info (int /*<<< orphan*/ ) ; 
 int sh_mobile_lcdc_overlay_fb_init (struct sh_mobile_lcdc_overlay*) ; 

__attribute__((used)) static int
sh_mobile_lcdc_overlay_init(struct sh_mobile_lcdc_overlay *ovl)
{
	const struct sh_mobile_lcdc_format_info *format;
	struct device *dev = ovl->channel->lcdc->dev;
	int ret;

	if (ovl->cfg->fourcc == 0)
		return 0;

	/* Validate the format. */
	format = sh_mobile_format_info(ovl->cfg->fourcc);
	if (format == NULL) {
		dev_err(dev, "Invalid FOURCC %08x\n", ovl->cfg->fourcc);
		return -EINVAL;
	}

	ovl->enabled = false;
	ovl->mode = LCDC_OVERLAY_BLEND;
	ovl->alpha = 255;
	ovl->rop3 = 0;
	ovl->pos_x = 0;
	ovl->pos_y = 0;

	/* The default Y virtual resolution is twice the panel size to allow for
	 * double-buffering.
	 */
	ovl->format = format;
	ovl->xres = ovl->cfg->max_xres;
	ovl->xres_virtual = ovl->xres;
	ovl->yres = ovl->cfg->max_yres;
	ovl->yres_virtual = ovl->yres * 2;

	if (!format->yuv)
		ovl->pitch = ovl->xres_virtual * format->bpp / 8;
	else
		ovl->pitch = ovl->xres_virtual;

	/* Allocate frame buffer memory. */
	ovl->fb_size = ovl->cfg->max_xres * ovl->cfg->max_yres
		       * format->bpp / 8 * 2;
	ovl->fb_mem = dma_alloc_coherent(dev, ovl->fb_size, &ovl->dma_handle,
					 GFP_KERNEL);
	if (!ovl->fb_mem) {
		dev_err(dev, "unable to allocate buffer\n");
		return -ENOMEM;
	}

	ret = sh_mobile_lcdc_overlay_fb_init(ovl);
	if (ret < 0)
		return ret;

	return 0;
}