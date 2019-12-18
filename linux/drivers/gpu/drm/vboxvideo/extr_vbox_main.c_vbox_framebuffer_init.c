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
struct vbox_private {int /*<<< orphan*/  ddev; } ;
struct vbox_framebuffer {int /*<<< orphan*/  base; struct drm_gem_object* obj; } ;
struct drm_mode_fb_cmd2 {int dummy; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int drm_framebuffer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_helper_mode_fill_fb_struct (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct drm_mode_fb_cmd2 const*) ; 
 int /*<<< orphan*/  vbox_fb_funcs ; 

int vbox_framebuffer_init(struct vbox_private *vbox,
			  struct vbox_framebuffer *vbox_fb,
			  const struct drm_mode_fb_cmd2 *mode_cmd,
			  struct drm_gem_object *obj)
{
	int ret;

	drm_helper_mode_fill_fb_struct(&vbox->ddev, &vbox_fb->base, mode_cmd);
	vbox_fb->obj = obj;
	ret = drm_framebuffer_init(&vbox->ddev, &vbox_fb->base, &vbox_fb_funcs);
	if (ret) {
		DRM_ERROR("framebuffer init failed %d\n", ret);
		return ret;
	}

	return 0;
}