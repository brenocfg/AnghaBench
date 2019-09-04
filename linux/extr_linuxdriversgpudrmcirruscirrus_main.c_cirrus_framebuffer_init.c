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
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  cirrus_fb_funcs ; 
 int drm_framebuffer_init (struct drm_device*,struct drm_framebuffer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_helper_mode_fill_fb_struct (struct drm_device*,struct drm_framebuffer*,struct drm_mode_fb_cmd2 const*) ; 

int cirrus_framebuffer_init(struct drm_device *dev,
			    struct drm_framebuffer *gfb,
			    const struct drm_mode_fb_cmd2 *mode_cmd,
			    struct drm_gem_object *obj)
{
	int ret;

	drm_helper_mode_fill_fb_struct(dev, gfb, mode_cmd);
	gfb->obj[0] = obj;
	ret = drm_framebuffer_init(dev, gfb, &cirrus_fb_funcs);
	if (ret) {
		DRM_ERROR("drm_framebuffer_init failed: %d\n", ret);
		return ret;
	}
	return 0;
}