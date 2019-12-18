#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct udl_fbdev {int /*<<< orphan*/  helper; } ;
struct udl_device {struct udl_fbdev* fbdev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_fb_helper_fini (int /*<<< orphan*/ *) ; 
 int drm_fb_helper_init (struct drm_device*,int /*<<< orphan*/ *,int) ; 
 int drm_fb_helper_initial_config (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drm_fb_helper_prepare (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_fb_helper_single_add_all_connectors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_helper_disable_unused_functions (struct drm_device*) ; 
 int fb_bpp ; 
 int /*<<< orphan*/  kfree (struct udl_fbdev*) ; 
 struct udl_fbdev* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct udl_device* to_udl (struct drm_device*) ; 
 int /*<<< orphan*/  udl_fb_helper_funcs ; 

int udl_fbdev_init(struct drm_device *dev)
{
	struct udl_device *udl = to_udl(dev);
	int bpp_sel = fb_bpp;
	struct udl_fbdev *ufbdev;
	int ret;

	ufbdev = kzalloc(sizeof(struct udl_fbdev), GFP_KERNEL);
	if (!ufbdev)
		return -ENOMEM;

	udl->fbdev = ufbdev;

	drm_fb_helper_prepare(dev, &ufbdev->helper, &udl_fb_helper_funcs);

	ret = drm_fb_helper_init(dev, &ufbdev->helper, 1);
	if (ret)
		goto free;

	ret = drm_fb_helper_single_add_all_connectors(&ufbdev->helper);
	if (ret)
		goto fini;

	/* disable all the possible outputs/crtcs before entering KMS mode */
	drm_helper_disable_unused_functions(dev);

	ret = drm_fb_helper_initial_config(&ufbdev->helper, bpp_sel);
	if (ret)
		goto fini;

	return 0;

fini:
	drm_fb_helper_fini(&ufbdev->helper);
free:
	kfree(ufbdev);
	return ret;
}