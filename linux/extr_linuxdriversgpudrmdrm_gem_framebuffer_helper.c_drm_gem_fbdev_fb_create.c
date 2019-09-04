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
struct drm_mode_fb_cmd2 {int width; int height; int* pitches; int /*<<< orphan*/  pixel_format; int /*<<< orphan*/  member_0; } ;
struct drm_gem_object {int size; } ;
struct drm_framebuffer_funcs {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_fb_helper_surface_size {int surface_width; int surface_height; int /*<<< orphan*/  surface_depth; int /*<<< orphan*/  surface_bpp; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EINVAL ; 
 struct drm_framebuffer* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct drm_framebuffer* drm_gem_fb_alloc (struct drm_device*,struct drm_mode_fb_cmd2*,struct drm_gem_object**,int,struct drm_framebuffer_funcs const*) ; 
 struct drm_framebuffer_funcs drm_gem_fb_funcs ; 
 int /*<<< orphan*/  drm_mode_legacy_fb_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int roundup (int,unsigned int) ; 

struct drm_framebuffer *
drm_gem_fbdev_fb_create(struct drm_device *dev,
			struct drm_fb_helper_surface_size *sizes,
			unsigned int pitch_align, struct drm_gem_object *obj,
			const struct drm_framebuffer_funcs *funcs)
{
	struct drm_mode_fb_cmd2 mode_cmd = { 0 };

	mode_cmd.width = sizes->surface_width;
	mode_cmd.height = sizes->surface_height;
	mode_cmd.pitches[0] = sizes->surface_width *
			      DIV_ROUND_UP(sizes->surface_bpp, 8);
	if (pitch_align)
		mode_cmd.pitches[0] = roundup(mode_cmd.pitches[0],
					      pitch_align);
	mode_cmd.pixel_format = drm_mode_legacy_fb_format(sizes->surface_bpp,
							sizes->surface_depth);
	if (obj->size < mode_cmd.pitches[0] * mode_cmd.height)
		return ERR_PTR(-EINVAL);

	if (!funcs)
		funcs = &drm_gem_fb_funcs;

	return drm_gem_fb_alloc(dev, &mode_cmd, &obj, 1, funcs);
}