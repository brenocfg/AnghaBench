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
typedef  int u32 ;
struct drm_mode_fb_cmd2 {int /*<<< orphan*/ * handles; int /*<<< orphan*/ * pitches; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixel_format; } ;
struct drm_gem_object {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {struct cirrus_device* dev_private; } ;
struct cirrus_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 struct drm_framebuffer* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cirrus_check_framebuffer (struct cirrus_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int cirrus_framebuffer_init (struct drm_device*,struct drm_framebuffer*,struct drm_mode_fb_cmd2 const*,struct drm_gem_object*) ; 
 int drm_format_plane_cpp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 int /*<<< orphan*/  kfree (struct drm_framebuffer*) ; 
 struct drm_framebuffer* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_framebuffer *
cirrus_user_framebuffer_create(struct drm_device *dev,
			       struct drm_file *filp,
			       const struct drm_mode_fb_cmd2 *mode_cmd)
{
	struct cirrus_device *cdev = dev->dev_private;
	struct drm_gem_object *obj;
	struct drm_framebuffer *fb;
	u32 bpp;
	int ret;

	bpp = drm_format_plane_cpp(mode_cmd->pixel_format, 0) * 8;

	if (!cirrus_check_framebuffer(cdev, mode_cmd->width, mode_cmd->height,
				      bpp, mode_cmd->pitches[0]))
		return ERR_PTR(-EINVAL);

	obj = drm_gem_object_lookup(filp, mode_cmd->handles[0]);
	if (obj == NULL)
		return ERR_PTR(-ENOENT);

	fb = kzalloc(sizeof(*fb), GFP_KERNEL);
	if (!fb) {
		drm_gem_object_put_unlocked(obj);
		return ERR_PTR(-ENOMEM);
	}

	ret = cirrus_framebuffer_init(dev, fb, mode_cmd, obj);
	if (ret) {
		drm_gem_object_put_unlocked(obj);
		kfree(fb);
		return ERR_PTR(ret);
	}
	return fb;
}