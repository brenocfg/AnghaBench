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
struct drm_framebuffer {int dummy; } ;
struct hibmc_framebuffer {struct drm_framebuffer fb; } ;
struct drm_mode_fb_cmd2 {int pixel_format; int /*<<< orphan*/ * handles; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 long ENOENT ; 
 struct drm_framebuffer* ERR_PTR (long) ; 
 scalar_t__ IS_ERR (struct hibmc_framebuffer*) ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 struct hibmc_framebuffer* hibmc_framebuffer_init (struct drm_device*,struct drm_mode_fb_cmd2 const*,struct drm_gem_object*) ; 

__attribute__((used)) static struct drm_framebuffer *
hibmc_user_framebuffer_create(struct drm_device *dev,
			      struct drm_file *filp,
			      const struct drm_mode_fb_cmd2 *mode_cmd)
{
	struct drm_gem_object *obj;
	struct hibmc_framebuffer *hibmc_fb;

	DRM_DEBUG_DRIVER("%dx%d, format %c%c%c%c\n",
			 mode_cmd->width, mode_cmd->height,
			 (mode_cmd->pixel_format) & 0xff,
			 (mode_cmd->pixel_format >> 8)  & 0xff,
			 (mode_cmd->pixel_format >> 16) & 0xff,
			 (mode_cmd->pixel_format >> 24) & 0xff);

	obj = drm_gem_object_lookup(filp, mode_cmd->handles[0]);
	if (!obj)
		return ERR_PTR(-ENOENT);

	hibmc_fb = hibmc_framebuffer_init(dev, mode_cmd, obj);
	if (IS_ERR(hibmc_fb)) {
		drm_gem_object_put_unlocked(obj);
		return ERR_PTR((long)hibmc_fb);
	}
	return &hibmc_fb->fb;
}