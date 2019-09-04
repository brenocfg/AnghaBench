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
struct qxl_framebuffer {struct drm_framebuffer base; } ;
struct drm_mode_fb_cmd2 {int /*<<< orphan*/ * handles; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 int /*<<< orphan*/  kfree (struct qxl_framebuffer*) ; 
 struct qxl_framebuffer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qxl_fb_funcs ; 
 int qxl_framebuffer_init (struct drm_device*,struct qxl_framebuffer*,struct drm_mode_fb_cmd2 const*,struct drm_gem_object*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct drm_framebuffer *
qxl_user_framebuffer_create(struct drm_device *dev,
			    struct drm_file *file_priv,
			    const struct drm_mode_fb_cmd2 *mode_cmd)
{
	struct drm_gem_object *obj;
	struct qxl_framebuffer *qxl_fb;
	int ret;

	obj = drm_gem_object_lookup(file_priv, mode_cmd->handles[0]);
	if (!obj)
		return NULL;

	qxl_fb = kzalloc(sizeof(*qxl_fb), GFP_KERNEL);
	if (qxl_fb == NULL)
		return NULL;

	ret = qxl_framebuffer_init(dev, qxl_fb, mode_cmd, obj, &qxl_fb_funcs);
	if (ret) {
		kfree(qxl_fb);
		drm_gem_object_put_unlocked(obj);
		return NULL;
	}

	return &qxl_fb->base;
}