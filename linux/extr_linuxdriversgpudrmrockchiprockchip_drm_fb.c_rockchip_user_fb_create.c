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
struct drm_mode_fb_cmd2 {unsigned int width; unsigned int height; unsigned int* pitches; unsigned int* offsets; int /*<<< orphan*/  pixel_format; int /*<<< orphan*/ * handles; } ;
struct drm_gem_object {unsigned int size; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int ENXIO ; 
 struct drm_framebuffer* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct drm_framebuffer*) ; 
 int PTR_ERR (struct drm_framebuffer*) ; 
 int ROCKCHIP_MAX_FB_BUFFER ; 
 unsigned int drm_format_horz_chroma_subsampling (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_format_num_planes (int /*<<< orphan*/ ) ; 
 unsigned int drm_format_plane_cpp (int /*<<< orphan*/ ,int) ; 
 unsigned int drm_format_vert_chroma_subsampling (int /*<<< orphan*/ ) ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (struct drm_gem_object*) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 struct drm_framebuffer* rockchip_fb_alloc (struct drm_device*,struct drm_mode_fb_cmd2 const*,struct drm_gem_object**,int) ; 

__attribute__((used)) static struct drm_framebuffer *
rockchip_user_fb_create(struct drm_device *dev, struct drm_file *file_priv,
			const struct drm_mode_fb_cmd2 *mode_cmd)
{
	struct drm_framebuffer *fb;
	struct drm_gem_object *objs[ROCKCHIP_MAX_FB_BUFFER];
	struct drm_gem_object *obj;
	unsigned int hsub;
	unsigned int vsub;
	int num_planes;
	int ret;
	int i;

	hsub = drm_format_horz_chroma_subsampling(mode_cmd->pixel_format);
	vsub = drm_format_vert_chroma_subsampling(mode_cmd->pixel_format);
	num_planes = min(drm_format_num_planes(mode_cmd->pixel_format),
			 ROCKCHIP_MAX_FB_BUFFER);

	for (i = 0; i < num_planes; i++) {
		unsigned int width = mode_cmd->width / (i ? hsub : 1);
		unsigned int height = mode_cmd->height / (i ? vsub : 1);
		unsigned int min_size;

		obj = drm_gem_object_lookup(file_priv, mode_cmd->handles[i]);
		if (!obj) {
			DRM_DEV_ERROR(dev->dev,
				      "Failed to lookup GEM object\n");
			ret = -ENXIO;
			goto err_gem_object_unreference;
		}

		min_size = (height - 1) * mode_cmd->pitches[i] +
			mode_cmd->offsets[i] +
			width * drm_format_plane_cpp(mode_cmd->pixel_format, i);

		if (obj->size < min_size) {
			drm_gem_object_put_unlocked(obj);
			ret = -EINVAL;
			goto err_gem_object_unreference;
		}
		objs[i] = obj;
	}

	fb = rockchip_fb_alloc(dev, mode_cmd, objs, i);
	if (IS_ERR(fb)) {
		ret = PTR_ERR(fb);
		goto err_gem_object_unreference;
	}

	return fb;

err_gem_object_unreference:
	for (i--; i >= 0; i--)
		drm_gem_object_put_unlocked(objs[i]);
	return ERR_PTR(ret);
}