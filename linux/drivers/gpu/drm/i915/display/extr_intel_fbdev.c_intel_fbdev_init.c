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
struct intel_fbdev {int preferred_bpp; int /*<<< orphan*/  helper; int /*<<< orphan*/  hpd_lock; } ;
struct drm_i915_private {int /*<<< orphan*/  fbdev_suspend_work; struct intel_fbdev* fbdev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HAS_DISPLAY (struct drm_i915_private*) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int drm_fb_helper_init (struct drm_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drm_fb_helper_prepare (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_fb_helper_single_add_all_connectors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_fb_helper_funcs ; 
 int /*<<< orphan*/  intel_fbdev_init_bios (struct drm_device*,struct intel_fbdev*) ; 
 int /*<<< orphan*/  intel_fbdev_suspend_worker ; 
 int /*<<< orphan*/  kfree (struct intel_fbdev*) ; 
 struct intel_fbdev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

int intel_fbdev_init(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct intel_fbdev *ifbdev;
	int ret;

	if (WARN_ON(!HAS_DISPLAY(dev_priv)))
		return -ENODEV;

	ifbdev = kzalloc(sizeof(struct intel_fbdev), GFP_KERNEL);
	if (ifbdev == NULL)
		return -ENOMEM;

	mutex_init(&ifbdev->hpd_lock);
	drm_fb_helper_prepare(dev, &ifbdev->helper, &intel_fb_helper_funcs);

	if (!intel_fbdev_init_bios(dev, ifbdev))
		ifbdev->preferred_bpp = 32;

	ret = drm_fb_helper_init(dev, &ifbdev->helper, 4);
	if (ret) {
		kfree(ifbdev);
		return ret;
	}

	dev_priv->fbdev = ifbdev;
	INIT_WORK(&dev_priv->fbdev_suspend_work, intel_fbdev_suspend_worker);

	drm_fb_helper_single_add_all_connectors(&ifbdev->helper);

	return 0;
}