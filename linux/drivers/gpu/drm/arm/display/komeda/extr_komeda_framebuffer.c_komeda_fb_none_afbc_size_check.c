#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  size_t u32 ;
struct drm_framebuffer {size_t* pitches; struct drm_format_info* format; int /*<<< orphan*/  height; struct drm_gem_object** obj; int /*<<< orphan*/  width; } ;
struct komeda_fb {struct drm_framebuffer base; } ;
struct TYPE_3__ {size_t bus_width; } ;
struct komeda_dev {TYPE_1__ chip; } ;
struct drm_mode_fb_cmd2 {int /*<<< orphan*/ * handles; } ;
struct drm_gem_object {scalar_t__ size; } ;
struct drm_format_info {size_t num_planes; } ;
struct drm_file {int dummy; } ;
struct TYPE_4__ {scalar_t__ paddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int EINVAL ; 
 int ENOENT ; 
 size_t drm_format_info_block_height (struct drm_format_info const*,size_t) ; 
 struct drm_gem_object* drm_gem_object_lookup (struct drm_file*,int /*<<< orphan*/ ) ; 
 scalar_t__ komeda_fb_check_src_coords (struct komeda_fb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ komeda_fb_get_pixel_addr (struct komeda_fb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 TYPE_2__* to_drm_gem_cma_obj (struct drm_gem_object*) ; 

__attribute__((used)) static int
komeda_fb_none_afbc_size_check(struct komeda_dev *mdev, struct komeda_fb *kfb,
			       struct drm_file *file,
			       const struct drm_mode_fb_cmd2 *mode_cmd)
{
	struct drm_framebuffer *fb = &kfb->base;
	const struct drm_format_info *info = fb->format;
	struct drm_gem_object *obj;
	u32 i, block_h;
	u64 min_size;

	if (komeda_fb_check_src_coords(kfb, 0, 0, fb->width, fb->height))
		return -EINVAL;

	for (i = 0; i < info->num_planes; i++) {
		obj = drm_gem_object_lookup(file, mode_cmd->handles[i]);
		if (!obj) {
			DRM_DEBUG_KMS("Failed to lookup GEM object\n");
			return -ENOENT;
		}
		fb->obj[i] = obj;

		block_h = drm_format_info_block_height(info, i);
		if ((fb->pitches[i] * block_h) % mdev->chip.bus_width) {
			DRM_DEBUG_KMS("Pitch[%d]: 0x%x doesn't align to 0x%x\n",
				      i, fb->pitches[i], mdev->chip.bus_width);
			return -EINVAL;
		}

		min_size = komeda_fb_get_pixel_addr(kfb, 0, fb->height, i)
			 - to_drm_gem_cma_obj(obj)->paddr;
		if (obj->size < min_size) {
			DRM_DEBUG_KMS("The fb->obj[%d] size: 0x%zx lower than the minimum requirement: 0x%llx.\n",
				      i, obj->size, min_size);
			return -EINVAL;
		}
	}

	if (fb->format->num_planes == 3) {
		if (fb->pitches[1] != fb->pitches[2]) {
			DRM_DEBUG_KMS("The pitch[1] and [2] are not same\n");
			return -EINVAL;
		}
	}

	return 0;
}