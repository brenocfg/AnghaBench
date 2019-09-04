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
struct drm_mode_fb_cmd2 {int /*<<< orphan*/ * handles; } ;
struct drm_gem_object {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct ast_framebuffer {struct drm_framebuffer base; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 struct drm_framebuffer* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ast_framebuffer_init (struct drm_device*,struct ast_framebuffer*,struct drm_mode_fb_cmd2 const*,struct drm_gem_object*) ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 int /*<<< orphan*/  kfree (struct ast_framebuffer*) ; 
 struct ast_framebuffer* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_framebuffer *
ast_user_framebuffer_create(struct drm_device *dev,
	       struct drm_file *filp,
	       const struct drm_mode_fb_cmd2 *mode_cmd)
{
	struct drm_gem_object *obj;
	struct ast_framebuffer *ast_fb;
	int ret;

	obj = drm_gem_object_lookup(filp, mode_cmd->handles[0]);
	if (obj == NULL)
		return ERR_PTR(-ENOENT);

	ast_fb = kzalloc(sizeof(*ast_fb), GFP_KERNEL);
	if (!ast_fb) {
		drm_gem_object_put_unlocked(obj);
		return ERR_PTR(-ENOMEM);
	}

	ret = ast_framebuffer_init(dev, ast_fb, mode_cmd, obj);
	if (ret) {
		drm_gem_object_put_unlocked(obj);
		kfree(ast_fb);
		return ERR_PTR(ret);
	}
	return &ast_fb->base;
}