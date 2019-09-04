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
struct qxl_framebuffer {struct drm_gem_object* obj; int /*<<< orphan*/  base; } ;
struct drm_mode_fb_cmd2 {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_framebuffer_funcs {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int drm_framebuffer_init (struct drm_device*,int /*<<< orphan*/ *,struct drm_framebuffer_funcs const*) ; 
 int /*<<< orphan*/  drm_helper_mode_fill_fb_struct (struct drm_device*,int /*<<< orphan*/ *,struct drm_mode_fb_cmd2 const*) ; 

int
qxl_framebuffer_init(struct drm_device *dev,
		     struct qxl_framebuffer *qfb,
		     const struct drm_mode_fb_cmd2 *mode_cmd,
		     struct drm_gem_object *obj,
		     const struct drm_framebuffer_funcs *funcs)
{
	int ret;

	qfb->obj = obj;
	drm_helper_mode_fill_fb_struct(dev, &qfb->base, mode_cmd);
	ret = drm_framebuffer_init(dev, &qfb->base, funcs);
	if (ret) {
		qfb->obj = NULL;
		return ret;
	}
	return 0;
}