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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct geodefb_par {scalar_t__ dc_regs; scalar_t__ vid_regs; int /*<<< orphan*/ * vid_ops; int /*<<< orphan*/ * dc_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; int /*<<< orphan*/  smem_len; } ;
struct fb_info {int /*<<< orphan*/  cmap; scalar_t__ screen_base; TYPE_1__ fix; int /*<<< orphan*/  var; struct geodefb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  cs5530_vid_ops ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int fb_find_mode (int /*<<< orphan*/ *,struct fb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fb_info (struct fb_info*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  gx1_dc_ops ; 
 scalar_t__ gx1_gx_base () ; 
 int /*<<< orphan*/  gx1_modedb ; 
 int /*<<< orphan*/  gx1fb_check_var (int /*<<< orphan*/ *,struct fb_info*) ; 
 struct fb_info* gx1fb_init_fbinfo (int /*<<< orphan*/ *) ; 
 int gx1fb_map_video_memory (struct fb_info*,struct pci_dev*) ; 
 int /*<<< orphan*/  gx1fb_set_par (struct fb_info*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  memset_io (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mode_option ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct fb_info*) ; 
 scalar_t__ register_framebuffer (struct fb_info*) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,int) ; 

__attribute__((used)) static int gx1fb_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct geodefb_par *par;
	struct fb_info *info;
	int ret;

	info = gx1fb_init_fbinfo(&pdev->dev);
	if (!info)
		return -ENOMEM;
	par = info->par;

	/* GX1 display controller and CS5530 video device */
	par->dc_ops  = &gx1_dc_ops;
	par->vid_ops = &cs5530_vid_ops;

	if ((ret = gx1fb_map_video_memory(info, pdev)) < 0) {
		dev_err(&pdev->dev, "failed to map frame buffer or controller registers\n");
		goto err;
	}

	ret = fb_find_mode(&info->var, info, mode_option,
			   gx1_modedb, ARRAY_SIZE(gx1_modedb), NULL, 16);
	if (ret == 0 || ret == 4) {
		dev_err(&pdev->dev, "could not find valid video mode\n");
		ret = -EINVAL;
		goto err;
	}

        /* Clear the frame buffer of garbage. */
        memset_io(info->screen_base, 0, info->fix.smem_len);

	gx1fb_check_var(&info->var, info);
	gx1fb_set_par(info);

	if (register_framebuffer(info) < 0) {
		ret = -EINVAL;
		goto err;
	}
	pci_set_drvdata(pdev, info);
	fb_info(info, "%s frame buffer device\n", info->fix.id);
	return 0;

  err:
	if (info->screen_base) {
		iounmap(info->screen_base);
		pci_release_region(pdev, 0);
	}
	if (par->vid_regs) {
		iounmap(par->vid_regs);
		pci_release_region(pdev, 1);
	}
	if (par->dc_regs) {
		iounmap(par->dc_regs);
		release_mem_region(gx1_gx_base() + 0x8300, 0x100);
	}

	fb_dealloc_cmap(&info->cmap);
	framebuffer_release(info);

	return ret;
}