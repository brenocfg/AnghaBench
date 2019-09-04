#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mga_fbdev {int /*<<< orphan*/  helper; int /*<<< orphan*/  dirty_lock; } ;
struct TYPE_5__ {int vram_size; } ;
struct mga_device {struct mga_fbdev* mfbdev; TYPE_2__* dev; TYPE_1__ mc; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_G200_SE (struct mga_device*) ; 
 int /*<<< orphan*/  MGAG200FB_CONN_LIMIT ; 
 struct mga_fbdev* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fb_helper_fini (int /*<<< orphan*/ *) ; 
 int drm_fb_helper_init (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int drm_fb_helper_initial_config (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drm_fb_helper_prepare (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_fb_helper_single_add_all_connectors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_helper_disable_unused_functions (TYPE_2__*) ; 
 int /*<<< orphan*/  mga_fb_helper_funcs ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int mgag200_fbdev_init(struct mga_device *mdev)
{
	struct mga_fbdev *mfbdev;
	int ret;
	int bpp_sel = 32;

	/* prefer 16bpp on low end gpus with limited VRAM */
	if (IS_G200_SE(mdev) && mdev->mc.vram_size < (2048*1024))
		bpp_sel = 16;

	mfbdev = devm_kzalloc(mdev->dev->dev, sizeof(struct mga_fbdev), GFP_KERNEL);
	if (!mfbdev)
		return -ENOMEM;

	mdev->mfbdev = mfbdev;
	spin_lock_init(&mfbdev->dirty_lock);

	drm_fb_helper_prepare(mdev->dev, &mfbdev->helper, &mga_fb_helper_funcs);

	ret = drm_fb_helper_init(mdev->dev, &mfbdev->helper,
				 MGAG200FB_CONN_LIMIT);
	if (ret)
		goto err_fb_helper;

	ret = drm_fb_helper_single_add_all_connectors(&mfbdev->helper);
	if (ret)
		goto err_fb_setup;

	/* disable all the possible outputs/crtcs before entering KMS mode */
	drm_helper_disable_unused_functions(mdev->dev);

	ret = drm_fb_helper_initial_config(&mfbdev->helper, bpp_sel);
	if (ret)
		goto err_fb_setup;

	return 0;

err_fb_setup:
	drm_fb_helper_fini(&mfbdev->helper);
err_fb_helper:
	mdev->mfbdev = NULL;

	return ret;
}