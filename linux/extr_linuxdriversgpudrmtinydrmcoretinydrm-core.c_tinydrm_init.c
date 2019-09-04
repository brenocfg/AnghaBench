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
struct tinydrm_device {struct drm_device* drm; struct drm_framebuffer_funcs const* fb_funcs; int /*<<< orphan*/  dirty_lock; } ;
struct drm_framebuffer_funcs {int dummy; } ;
struct drm_driver {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * funcs; } ;
struct drm_device {TYPE_1__ mode_config; struct tinydrm_device* dev_private; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct drm_device*) ; 
 int PTR_ERR (struct drm_device*) ; 
 struct drm_device* drm_dev_alloc (struct drm_driver*,struct device*) ; 
 int /*<<< orphan*/  drm_mode_config_init (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tinydrm_mode_config_funcs ; 

__attribute__((used)) static int tinydrm_init(struct device *parent, struct tinydrm_device *tdev,
			const struct drm_framebuffer_funcs *fb_funcs,
			struct drm_driver *driver)
{
	struct drm_device *drm;

	mutex_init(&tdev->dirty_lock);
	tdev->fb_funcs = fb_funcs;

	/*
	 * We don't embed drm_device, because that prevent us from using
	 * devm_kzalloc() to allocate tinydrm_device in the driver since
	 * drm_dev_unref() frees the structure. The devm_ functions provide
	 * for easy error handling.
	 */
	drm = drm_dev_alloc(driver, parent);
	if (IS_ERR(drm))
		return PTR_ERR(drm);

	tdev->drm = drm;
	drm->dev_private = tdev;
	drm_mode_config_init(drm);
	drm->mode_config.funcs = &tinydrm_mode_config_funcs;

	return 0;
}