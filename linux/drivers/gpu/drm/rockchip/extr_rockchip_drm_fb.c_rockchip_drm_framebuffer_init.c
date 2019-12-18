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
struct drm_framebuffer {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 struct drm_framebuffer* ERR_CAST (struct drm_framebuffer*) ; 
 scalar_t__ IS_ERR (struct drm_framebuffer*) ; 
 struct drm_framebuffer* rockchip_fb_alloc (struct drm_device*,struct drm_mode_fb_cmd2 const*,struct drm_gem_object**,int) ; 

struct drm_framebuffer *
rockchip_drm_framebuffer_init(struct drm_device *dev,
			      const struct drm_mode_fb_cmd2 *mode_cmd,
			      struct drm_gem_object *obj)
{
	struct drm_framebuffer *fb;

	fb = rockchip_fb_alloc(dev, mode_cmd, &obj, 1);
	if (IS_ERR(fb))
		return ERR_CAST(fb);

	return fb;
}