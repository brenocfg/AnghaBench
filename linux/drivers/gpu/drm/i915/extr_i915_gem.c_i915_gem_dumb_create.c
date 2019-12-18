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
typedef  int /*<<< orphan*/  u32 ;
struct drm_mode_create_dumb {int pitch; int width; int size; int height; int /*<<< orphan*/  handle; int /*<<< orphan*/  bpp; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 void* ALIGN (int,int) ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_FORMAT_C8 ; 
 int /*<<< orphan*/  DRM_FORMAT_MOD_LINEAR ; 
 int /*<<< orphan*/  DRM_FORMAT_RGB565 ; 
 int /*<<< orphan*/  DRM_FORMAT_XRGB8888 ; 
 int EINVAL ; 
 int i915_gem_create (struct drm_file*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int intel_plane_fb_max_stride (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_i915 (struct drm_device*) ; 

int
i915_gem_dumb_create(struct drm_file *file,
		     struct drm_device *dev,
		     struct drm_mode_create_dumb *args)
{
	int cpp = DIV_ROUND_UP(args->bpp, 8);
	u32 format;

	switch (cpp) {
	case 1:
		format = DRM_FORMAT_C8;
		break;
	case 2:
		format = DRM_FORMAT_RGB565;
		break;
	case 4:
		format = DRM_FORMAT_XRGB8888;
		break;
	default:
		return -EINVAL;
	}

	/* have to work out size/pitch and return them */
	args->pitch = ALIGN(args->width * cpp, 64);

	/* align stride to page size so that we can remap */
	if (args->pitch > intel_plane_fb_max_stride(to_i915(dev), format,
						    DRM_FORMAT_MOD_LINEAR))
		args->pitch = ALIGN(args->pitch, 4096);

	args->size = args->pitch * args->height;
	return i915_gem_create(file, to_i915(dev),
			       &args->size, &args->handle);
}