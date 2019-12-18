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
struct omap_fbdev {int /*<<< orphan*/  work; int /*<<< orphan*/  ywrap_enabled; } ;
struct omap_drm_private {int /*<<< orphan*/  wq; } ;
struct fb_var_screeninfo {int dummy; } ;
struct fb_info {int dummy; } ;
struct drm_fb_helper {TYPE_1__* dev; } ;
struct TYPE_2__ {struct omap_drm_private* dev_private; } ;

/* Variables and functions */
 scalar_t__ drm_can_sleep () ; 
 int drm_fb_helper_pan_display (struct fb_var_screeninfo*,struct fb_info*) ; 
 struct drm_fb_helper* get_fb (struct fb_info*) ; 
 int /*<<< orphan*/  pan_worker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct omap_fbdev* to_omap_fbdev (struct drm_fb_helper*) ; 

__attribute__((used)) static int omap_fbdev_pan_display(struct fb_var_screeninfo *var,
		struct fb_info *fbi)
{
	struct drm_fb_helper *helper = get_fb(fbi);
	struct omap_fbdev *fbdev = to_omap_fbdev(helper);

	if (!helper)
		goto fallback;

	if (!fbdev->ywrap_enabled)
		goto fallback;

	if (drm_can_sleep()) {
		pan_worker(&fbdev->work);
	} else {
		struct omap_drm_private *priv = helper->dev->dev_private;
		queue_work(priv->wq, &fbdev->work);
	}

	return 0;

fallback:
	return drm_fb_helper_pan_display(var, fbi);
}