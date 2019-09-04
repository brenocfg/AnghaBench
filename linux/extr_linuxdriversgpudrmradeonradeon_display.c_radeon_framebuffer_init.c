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
struct drm_mode_fb_cmd2 {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_framebuffer {struct drm_gem_object** obj; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int drm_framebuffer_init (struct drm_device*,struct drm_framebuffer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_helper_mode_fill_fb_struct (struct drm_device*,struct drm_framebuffer*,struct drm_mode_fb_cmd2 const*) ; 
 int /*<<< orphan*/  radeon_fb_funcs ; 

int
radeon_framebuffer_init(struct drm_device *dev,
			struct drm_framebuffer *fb,
			const struct drm_mode_fb_cmd2 *mode_cmd,
			struct drm_gem_object *obj)
{
	int ret;
	fb->obj[0] = obj;
	drm_helper_mode_fill_fb_struct(dev, fb, mode_cmd);
	ret = drm_framebuffer_init(dev, fb, &radeon_fb_funcs);
	if (ret) {
		fb->obj[0] = NULL;
		return ret;
	}
	return 0;
}