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
struct mga_framebuffer {struct drm_framebuffer base; } ;
struct drm_mode_fb_cmd2 {int /*<<< orphan*/ * handles; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 struct drm_framebuffer* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 int /*<<< orphan*/  kfree (struct mga_framebuffer*) ; 
 struct mga_framebuffer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mgag200_framebuffer_init (struct drm_device*,struct mga_framebuffer*,struct drm_mode_fb_cmd2 const*,struct drm_gem_object*) ; 

__attribute__((used)) static struct drm_framebuffer *
mgag200_user_framebuffer_create(struct drm_device *dev,
				struct drm_file *filp,
				const struct drm_mode_fb_cmd2 *mode_cmd)
{
	struct drm_gem_object *obj;
	struct mga_framebuffer *mga_fb;
	int ret;

	obj = drm_gem_object_lookup(filp, mode_cmd->handles[0]);
	if (obj == NULL)
		return ERR_PTR(-ENOENT);

	mga_fb = kzalloc(sizeof(*mga_fb), GFP_KERNEL);
	if (!mga_fb) {
		drm_gem_object_put_unlocked(obj);
		return ERR_PTR(-ENOMEM);
	}

	ret = mgag200_framebuffer_init(dev, mga_fb, mode_cmd, obj);
	if (ret) {
		drm_gem_object_put_unlocked(obj);
		kfree(mga_fb);
		return ERR_PTR(ret);
	}
	return &mga_fb->base;
}