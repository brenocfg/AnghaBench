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
struct tegra_bo {int /*<<< orphan*/  gem; } ;
struct drm_mode_fb_cmd2 {unsigned int width; unsigned int height; unsigned int* pitches; unsigned int* offsets; int /*<<< orphan*/  pixel_format; int /*<<< orphan*/ * handles; } ;
struct drm_gem_object {unsigned int size; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 struct drm_framebuffer* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct drm_framebuffer*) ; 
 int PTR_ERR (struct drm_framebuffer*) ; 
 unsigned int drm_format_horz_chroma_subsampling (int /*<<< orphan*/ ) ; 
 unsigned int drm_format_num_planes (int /*<<< orphan*/ ) ; 
 unsigned int drm_format_plane_cpp (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int drm_format_vert_chroma_subsampling (int /*<<< orphan*/ ) ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 struct drm_framebuffer* tegra_fb_alloc (struct drm_device*,struct drm_mode_fb_cmd2 const*,struct tegra_bo**,unsigned int) ; 
 struct tegra_bo* to_tegra_bo (struct drm_gem_object*) ; 

struct drm_framebuffer *tegra_fb_create(struct drm_device *drm,
					struct drm_file *file,
					const struct drm_mode_fb_cmd2 *cmd)
{
	unsigned int hsub, vsub, i;
	struct tegra_bo *planes[4];
	struct drm_gem_object *gem;
	struct drm_framebuffer *fb;
	int err;

	hsub = drm_format_horz_chroma_subsampling(cmd->pixel_format);
	vsub = drm_format_vert_chroma_subsampling(cmd->pixel_format);

	for (i = 0; i < drm_format_num_planes(cmd->pixel_format); i++) {
		unsigned int width = cmd->width / (i ? hsub : 1);
		unsigned int height = cmd->height / (i ? vsub : 1);
		unsigned int size, bpp;

		gem = drm_gem_object_lookup(file, cmd->handles[i]);
		if (!gem) {
			err = -ENXIO;
			goto unreference;
		}

		bpp = drm_format_plane_cpp(cmd->pixel_format, i);

		size = (height - 1) * cmd->pitches[i] +
		       width * bpp + cmd->offsets[i];

		if (gem->size < size) {
			err = -EINVAL;
			goto unreference;
		}

		planes[i] = to_tegra_bo(gem);
	}

	fb = tegra_fb_alloc(drm, cmd, planes, i);
	if (IS_ERR(fb)) {
		err = PTR_ERR(fb);
		goto unreference;
	}

	return fb;

unreference:
	while (i--)
		drm_gem_object_put_unlocked(&planes[i]->gem);

	return ERR_PTR(err);
}