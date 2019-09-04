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
struct tinydrm_device {int dummy; } ;
struct drm_framebuffer_funcs {int dummy; } ;
struct drm_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int devm_add_action (struct device*,int /*<<< orphan*/ ,struct tinydrm_device*) ; 
 int /*<<< orphan*/  devm_tinydrm_release ; 
 int /*<<< orphan*/  tinydrm_fini (struct tinydrm_device*) ; 
 int tinydrm_init (struct device*,struct tinydrm_device*,struct drm_framebuffer_funcs const*,struct drm_driver*) ; 

int devm_tinydrm_init(struct device *parent, struct tinydrm_device *tdev,
		      const struct drm_framebuffer_funcs *fb_funcs,
		      struct drm_driver *driver)
{
	int ret;

	ret = tinydrm_init(parent, tdev, fb_funcs, driver);
	if (ret)
		return ret;

	ret = devm_add_action(parent, devm_tinydrm_release, tdev);
	if (ret)
		tinydrm_fini(tdev);

	return ret;
}