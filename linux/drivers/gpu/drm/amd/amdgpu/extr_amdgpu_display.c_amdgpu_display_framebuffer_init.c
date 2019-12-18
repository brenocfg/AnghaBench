#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_mode_fb_cmd2 {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_3__ {struct drm_gem_object** obj; } ;
struct amdgpu_framebuffer {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_fb_funcs ; 
 int drm_framebuffer_init (struct drm_device*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_helper_mode_fill_fb_struct (struct drm_device*,TYPE_1__*,struct drm_mode_fb_cmd2 const*) ; 

int amdgpu_display_framebuffer_init(struct drm_device *dev,
				    struct amdgpu_framebuffer *rfb,
				    const struct drm_mode_fb_cmd2 *mode_cmd,
				    struct drm_gem_object *obj)
{
	int ret;
	rfb->base.obj[0] = obj;
	drm_helper_mode_fill_fb_struct(dev, &rfb->base, mode_cmd);
	ret = drm_framebuffer_init(dev, &rfb->base, &amdgpu_fb_funcs);
	if (ret) {
		rfb->base.obj[0] = NULL;
		return ret;
	}
	return 0;
}