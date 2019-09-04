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
struct drm_mode_fb_cmd2 {int pixel_format; int /*<<< orphan*/ * handles; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct drm_gem_object {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct bochs_framebuffer {struct drm_framebuffer base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int DRM_FORMAT_XRGB8888 ; 
 int ENOENT ; 
 int ENOMEM ; 
 struct drm_framebuffer* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int bochs_framebuffer_init (struct drm_device*,struct bochs_framebuffer*,struct drm_mode_fb_cmd2 const*,struct drm_gem_object*) ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_unreference_unlocked (struct drm_gem_object*) ; 
 int /*<<< orphan*/  kfree (struct bochs_framebuffer*) ; 
 struct bochs_framebuffer* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_framebuffer *
bochs_user_framebuffer_create(struct drm_device *dev,
			      struct drm_file *filp,
			      const struct drm_mode_fb_cmd2 *mode_cmd)
{
	struct drm_gem_object *obj;
	struct bochs_framebuffer *bochs_fb;
	int ret;

	DRM_DEBUG_DRIVER("%dx%d, format %c%c%c%c\n",
	       mode_cmd->width, mode_cmd->height,
	       (mode_cmd->pixel_format)       & 0xff,
	       (mode_cmd->pixel_format >> 8)  & 0xff,
	       (mode_cmd->pixel_format >> 16) & 0xff,
	       (mode_cmd->pixel_format >> 24) & 0xff);

	if (mode_cmd->pixel_format != DRM_FORMAT_XRGB8888)
		return ERR_PTR(-ENOENT);

	obj = drm_gem_object_lookup(filp, mode_cmd->handles[0]);
	if (obj == NULL)
		return ERR_PTR(-ENOENT);

	bochs_fb = kzalloc(sizeof(*bochs_fb), GFP_KERNEL);
	if (!bochs_fb) {
		drm_gem_object_unreference_unlocked(obj);
		return ERR_PTR(-ENOMEM);
	}

	ret = bochs_framebuffer_init(dev, bochs_fb, mode_cmd, obj);
	if (ret) {
		drm_gem_object_unreference_unlocked(obj);
		kfree(bochs_fb);
		return ERR_PTR(ret);
	}
	return &bochs_fb->base;
}