#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {struct mmp_buffer_driver_mach_info* platform_data; } ;
struct platform_device {TYPE_5__ dev; } ;
struct mmpfb_info {int fb_size; TYPE_5__* dev; int /*<<< orphan*/  access_ok; int /*<<< orphan*/  fb_start_dma; int /*<<< orphan*/ * fb_start; int /*<<< orphan*/  overlay; TYPE_3__* path; int /*<<< orphan*/  pix_fmt; int /*<<< orphan*/  name; struct fb_info* fb_info; } ;
struct mmp_buffer_driver_mach_info {int /*<<< orphan*/  dmafetch_id; int /*<<< orphan*/  overlay_id; int /*<<< orphan*/  path_name; int /*<<< orphan*/  default_pixfmt; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {int /*<<< orphan*/  id; } ;
struct TYPE_11__ {int yres_virtual; int yres; int xres_virtual; int bits_per_pixel; } ;
struct fb_info {TYPE_1__ fix; int /*<<< orphan*/  node; TYPE_2__ var; struct mmpfb_info* par; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MMPFB_DEFAULT_SIZE ; 
 int /*<<< orphan*/  PAGE_ALIGN (int) ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_5__*,char*,int,...) ; 
 int /*<<< orphan*/ * dma_alloc_coherent (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_info_clear (struct fb_info*) ; 
 int fb_info_setup (struct fb_info*,struct mmpfb_info*) ; 
 int /*<<< orphan*/  fb_prepare_logo (struct fb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_show_logo (struct fb_info*,int /*<<< orphan*/ ) ; 
 struct fb_info* framebuffer_alloc (int,TYPE_5__*) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 TYPE_3__* mmp_get_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmp_overlay_set_fetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmp_path_get_overlay (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmpfb_power (struct mmpfb_info*,int) ; 
 int modes_setup (struct mmpfb_info*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pixfmt_to_var (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mmpfb_info*) ; 
 int register_framebuffer (struct fb_info*) ; 

__attribute__((used)) static int mmpfb_probe(struct platform_device *pdev)
{
	struct mmp_buffer_driver_mach_info *mi;
	struct fb_info *info;
	struct mmpfb_info *fbi;
	int ret, modes_num;

	mi = pdev->dev.platform_data;
	if (mi == NULL) {
		dev_err(&pdev->dev, "no platform data defined\n");
		return -EINVAL;
	}

	/* initialize fb */
	info = framebuffer_alloc(sizeof(struct mmpfb_info), &pdev->dev);
	if (info == NULL)
		return -ENOMEM;
	fbi = info->par;

	/* init fb */
	fbi->fb_info = info;
	platform_set_drvdata(pdev, fbi);
	fbi->dev = &pdev->dev;
	fbi->name = mi->name;
	fbi->pix_fmt = mi->default_pixfmt;
	pixfmt_to_var(&info->var, fbi->pix_fmt);
	mutex_init(&fbi->access_ok);

	/* get display path by name */
	fbi->path = mmp_get_path(mi->path_name);
	if (!fbi->path) {
		dev_err(&pdev->dev, "can't get the path %s\n", mi->path_name);
		ret = -EINVAL;
		goto failed_destroy_mutex;
	}

	dev_info(fbi->dev, "path %s get\n", fbi->path->name);

	/* get overlay */
	fbi->overlay = mmp_path_get_overlay(fbi->path, mi->overlay_id);
	if (!fbi->overlay) {
		ret = -EINVAL;
		goto failed_destroy_mutex;
	}
	/* set fetch used */
	mmp_overlay_set_fetch(fbi->overlay, mi->dmafetch_id);

	modes_num = modes_setup(fbi);
	if (modes_num < 0) {
		ret = modes_num;
		goto failed_destroy_mutex;
	}

	/*
	 * if get modes success, means not hotplug panels, use caculated buffer
	 * or use default size
	 */
	if (modes_num > 0) {
		/* fix to 2* yres */
		info->var.yres_virtual = info->var.yres * 2;

		/* Allocate framebuffer memory: size = modes xy *4 */
		fbi->fb_size = info->var.xres_virtual * info->var.yres_virtual
				* info->var.bits_per_pixel / 8;
	} else {
		fbi->fb_size = MMPFB_DEFAULT_SIZE;
	}

	fbi->fb_start = dma_alloc_coherent(&pdev->dev, PAGE_ALIGN(fbi->fb_size),
				&fbi->fb_start_dma, GFP_KERNEL);
	if (fbi->fb_start == NULL) {
		dev_err(&pdev->dev, "can't alloc framebuffer\n");
		ret = -ENOMEM;
		goto failed_destroy_mutex;
	}
	dev_info(fbi->dev, "fb %dk allocated\n", fbi->fb_size/1024);

	/* fb power on */
	if (modes_num > 0)
		mmpfb_power(fbi, 1);

	ret = fb_info_setup(info, fbi);
	if (ret < 0)
		goto failed_free_buff;

	ret = register_framebuffer(info);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to register fb: %d\n", ret);
		ret = -ENXIO;
		goto failed_clear_info;
	}

	dev_info(fbi->dev, "loaded to /dev/fb%d <%s>.\n",
		info->node, info->fix.id);

#ifdef CONFIG_LOGO
	if (fbi->fb_start) {
		fb_prepare_logo(info, 0);
		fb_show_logo(info, 0);
	}
#endif

	return 0;

failed_clear_info:
	fb_info_clear(info);
failed_free_buff:
	dma_free_coherent(&pdev->dev, PAGE_ALIGN(fbi->fb_size), fbi->fb_start,
		fbi->fb_start_dma);
failed_destroy_mutex:
	mutex_destroy(&fbi->access_ok);
	dev_err(fbi->dev, "mmp-fb: frame buffer device init failed\n");

	framebuffer_release(info);

	return ret;
}