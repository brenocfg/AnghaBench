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
struct fb_info {int skip_vt_switch; int /*<<< orphan*/  cmap; int /*<<< orphan*/  apertures; } ;
struct drm_fb_helper {struct fb_info* fbdev; TYPE_1__* dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct fb_info* ERR_PTR (int) ; 
 int /*<<< orphan*/  alloc_apertures (int) ; 
 int fb_alloc_cmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 struct fb_info* framebuffer_alloc (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 

struct fb_info *drm_fb_helper_alloc_fbi(struct drm_fb_helper *fb_helper)
{
	struct device *dev = fb_helper->dev->dev;
	struct fb_info *info;
	int ret;

	info = framebuffer_alloc(0, dev);
	if (!info)
		return ERR_PTR(-ENOMEM);

	ret = fb_alloc_cmap(&info->cmap, 256, 0);
	if (ret)
		goto err_release;

	info->apertures = alloc_apertures(1);
	if (!info->apertures) {
		ret = -ENOMEM;
		goto err_free_cmap;
	}

	fb_helper->fbdev = info;
	info->skip_vt_switch = true;

	return info;

err_free_cmap:
	fb_dealloc_cmap(&info->cmap);
err_release:
	framebuffer_release(info);
	return ERR_PTR(ret);
}