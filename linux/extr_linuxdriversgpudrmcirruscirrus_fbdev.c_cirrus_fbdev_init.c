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
struct cirrus_fbdev {int /*<<< orphan*/  helper; int /*<<< orphan*/  dirty_lock; } ;
struct TYPE_2__ {struct cirrus_fbdev* gfbdev; } ;
struct cirrus_device {int /*<<< orphan*/  dev; TYPE_1__ mode_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIRRUSFB_CONN_LIMIT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cirrus_fb_helper_funcs ; 
 int drm_fb_helper_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int drm_fb_helper_initial_config (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drm_fb_helper_prepare (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_fb_helper_single_add_all_connectors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_helper_disable_unused_functions (int /*<<< orphan*/ ) ; 
 struct cirrus_fbdev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int cirrus_fbdev_init(struct cirrus_device *cdev)
{
	struct cirrus_fbdev *gfbdev;
	int ret;
	int bpp_sel = 24;

	/*bpp_sel = 8;*/
	gfbdev = kzalloc(sizeof(struct cirrus_fbdev), GFP_KERNEL);
	if (!gfbdev)
		return -ENOMEM;

	cdev->mode_info.gfbdev = gfbdev;
	spin_lock_init(&gfbdev->dirty_lock);

	drm_fb_helper_prepare(cdev->dev, &gfbdev->helper,
			      &cirrus_fb_helper_funcs);

	ret = drm_fb_helper_init(cdev->dev, &gfbdev->helper,
				 CIRRUSFB_CONN_LIMIT);
	if (ret)
		return ret;

	ret = drm_fb_helper_single_add_all_connectors(&gfbdev->helper);
	if (ret)
		return ret;

	/* disable all the possible outputs/crtcs before entering KMS mode */
	drm_helper_disable_unused_functions(cdev->dev);

	return drm_fb_helper_initial_config(&gfbdev->helper, bpp_sel);
}