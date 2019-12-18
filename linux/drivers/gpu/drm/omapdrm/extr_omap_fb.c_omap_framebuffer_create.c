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
struct drm_format_info {unsigned int num_planes; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct drm_framebuffer* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct drm_framebuffer*) ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 struct drm_format_info* drm_get_format_info (struct drm_device*,struct drm_mode_fb_cmd2 const*) ; 
 struct drm_framebuffer* omap_framebuffer_init (struct drm_device*,struct drm_mode_fb_cmd2 const*,struct drm_gem_object**) ; 

struct drm_framebuffer *omap_framebuffer_create(struct drm_device *dev,
		struct drm_file *file, const struct drm_mode_fb_cmd2 *mode_cmd)
{
	const struct drm_format_info *info = drm_get_format_info(dev,
								 mode_cmd);
	unsigned int num_planes = info->num_planes;
	struct drm_gem_object *bos[4];
	struct drm_framebuffer *fb;
	int i;

	for (i = 0; i < num_planes; i++) {
		bos[i] = drm_gem_object_lookup(file, mode_cmd->handles[i]);
		if (!bos[i]) {
			fb = ERR_PTR(-ENOENT);
			goto error;
		}
	}

	fb = omap_framebuffer_init(dev, mode_cmd, bos);
	if (IS_ERR(fb))
		goto error;

	return fb;

error:
	while (--i >= 0)
		drm_gem_object_put_unlocked(bos[i]);

	return fb;
}