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
struct drm_device {struct ast_private* dev_private; } ;
struct ast_private {struct ast_fbdev* fbdev; } ;
struct ast_fbdev {int /*<<< orphan*/  helper; int /*<<< orphan*/  dirty_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ast_fb_helper_funcs ; 
 int /*<<< orphan*/  drm_fb_helper_fini (int /*<<< orphan*/ *) ; 
 int drm_fb_helper_init (struct drm_device*,int /*<<< orphan*/ *,int) ; 
 int drm_fb_helper_initial_config (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drm_fb_helper_prepare (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_fb_helper_single_add_all_connectors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_helper_disable_unused_functions (struct drm_device*) ; 
 int /*<<< orphan*/  kfree (struct ast_fbdev*) ; 
 struct ast_fbdev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int ast_fbdev_init(struct drm_device *dev)
{
	struct ast_private *ast = dev->dev_private;
	struct ast_fbdev *afbdev;
	int ret;

	afbdev = kzalloc(sizeof(struct ast_fbdev), GFP_KERNEL);
	if (!afbdev)
		return -ENOMEM;

	ast->fbdev = afbdev;
	spin_lock_init(&afbdev->dirty_lock);

	drm_fb_helper_prepare(dev, &afbdev->helper, &ast_fb_helper_funcs);

	ret = drm_fb_helper_init(dev, &afbdev->helper, 1);
	if (ret)
		goto free;

	ret = drm_fb_helper_single_add_all_connectors(&afbdev->helper);
	if (ret)
		goto fini;

	/* disable all the possible outputs/crtcs before entering KMS mode */
	drm_helper_disable_unused_functions(dev);

	ret = drm_fb_helper_initial_config(&afbdev->helper, 32);
	if (ret)
		goto fini;

	return 0;

fini:
	drm_fb_helper_fini(&afbdev->helper);
free:
	kfree(afbdev);
	return ret;
}