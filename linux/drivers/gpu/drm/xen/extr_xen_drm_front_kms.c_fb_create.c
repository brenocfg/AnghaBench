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
struct xen_drm_front_drm_info {int /*<<< orphan*/  front_info; } ;
struct drm_mode_fb_cmd2 {int /*<<< orphan*/ * handles; } ;
struct drm_gem_object {int dummy; } ;
struct drm_framebuffer {TYPE_1__* format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct drm_file {int dummy; } ;
struct drm_device {struct xen_drm_front_drm_info* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int ENOENT ; 
 struct drm_framebuffer* ERR_PTR (int) ; 
 scalar_t__ IS_ERR_OR_NULL (struct drm_framebuffer*) ; 
 struct drm_framebuffer* drm_gem_fb_create_with_funcs (struct drm_device*,struct drm_file*,struct drm_mode_fb_cmd2 const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_fb_destroy (struct drm_framebuffer*) ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 int /*<<< orphan*/  fb_funcs ; 
 int /*<<< orphan*/  xen_drm_front_dbuf_to_cookie (struct drm_gem_object*) ; 
 int xen_drm_front_fb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_drm_front_fb_to_cookie (struct drm_framebuffer*) ; 

__attribute__((used)) static struct drm_framebuffer *
fb_create(struct drm_device *dev, struct drm_file *filp,
	  const struct drm_mode_fb_cmd2 *mode_cmd)
{
	struct xen_drm_front_drm_info *drm_info = dev->dev_private;
	struct drm_framebuffer *fb;
	struct drm_gem_object *gem_obj;
	int ret;

	fb = drm_gem_fb_create_with_funcs(dev, filp, mode_cmd, &fb_funcs);
	if (IS_ERR_OR_NULL(fb))
		return fb;

	gem_obj = drm_gem_object_lookup(filp, mode_cmd->handles[0]);
	if (!gem_obj) {
		DRM_ERROR("Failed to lookup GEM object\n");
		ret = -ENOENT;
		goto fail;
	}

	drm_gem_object_put_unlocked(gem_obj);

	ret = xen_drm_front_fb_attach(drm_info->front_info,
				      xen_drm_front_dbuf_to_cookie(gem_obj),
				      xen_drm_front_fb_to_cookie(fb),
				      fb->width, fb->height,
				      fb->format->format);
	if (ret < 0) {
		DRM_ERROR("Back failed to attach FB %p: %d\n", fb, ret);
		goto fail;
	}

	return fb;

fail:
	drm_gem_fb_destroy(fb);
	return ERR_PTR(ret);
}