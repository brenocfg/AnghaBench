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
struct drm_mode_fb_cmd2 {unsigned int width; unsigned int height; unsigned int* pitches; scalar_t__* offsets; int /*<<< orphan*/ * handles; } ;
struct drm_gem_object {unsigned int size; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_format_info {int num_planes; unsigned int* cpp; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 struct drm_framebuffer* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct drm_framebuffer*) ; 
 int PTR_ERR (struct drm_framebuffer*) ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 struct drm_format_info* drm_get_format_info (struct drm_device*,struct drm_mode_fb_cmd2 const*) ; 
 struct drm_framebuffer* mtk_drm_framebuffer_init (struct drm_device*,struct drm_mode_fb_cmd2 const*,struct drm_gem_object*) ; 

struct drm_framebuffer *mtk_drm_mode_fb_create(struct drm_device *dev,
					       struct drm_file *file,
					       const struct drm_mode_fb_cmd2 *cmd)
{
	const struct drm_format_info *info = drm_get_format_info(dev, cmd);
	struct drm_framebuffer *fb;
	struct drm_gem_object *gem;
	unsigned int width = cmd->width;
	unsigned int height = cmd->height;
	unsigned int size, bpp;
	int ret;

	if (info->num_planes != 1)
		return ERR_PTR(-EINVAL);

	gem = drm_gem_object_lookup(file, cmd->handles[0]);
	if (!gem)
		return ERR_PTR(-ENOENT);

	bpp = info->cpp[0];
	size = (height - 1) * cmd->pitches[0] + width * bpp;
	size += cmd->offsets[0];

	if (gem->size < size) {
		ret = -EINVAL;
		goto unreference;
	}

	fb = mtk_drm_framebuffer_init(dev, cmd, gem);
	if (IS_ERR(fb)) {
		ret = PTR_ERR(fb);
		goto unreference;
	}

	return fb;

unreference:
	drm_gem_object_put_unlocked(gem);
	return ERR_PTR(ret);
}