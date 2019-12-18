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
struct radeon_fbdev {struct radeon_device* rdev; } ;
struct radeon_device {scalar_t__ family; int /*<<< orphan*/  dev; int /*<<< orphan*/  ddev; } ;
struct radeon_bo {int dummy; } ;
struct drm_mode_fb_cmd2 {int height; int* pitches; int /*<<< orphan*/  width; } ;
struct drm_gem_object {int dummy; } ;
struct drm_format_info {int* cpp; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 
 scalar_t__ CHIP_R600 ; 
 int ENOMEM ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  RADEON_GEM_DOMAIN_VRAM ; 
 int RADEON_TILING_MACRO ; 
 int RADEON_TILING_SURFACE ; 
 int RADEON_TILING_SWAP_16BIT ; 
 int RADEON_TILING_SWAP_32BIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct drm_format_info* drm_get_format_info (int /*<<< orphan*/ ,struct drm_mode_fb_cmd2*) ; 
 struct radeon_bo* gem_to_radeon_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int radeon_align_pitch (struct radeon_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  radeon_bo_check_tiling (struct radeon_bo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int radeon_bo_kmap (struct radeon_bo*,int /*<<< orphan*/ *) ; 
 int radeon_bo_pin_restricted (struct radeon_bo*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int radeon_bo_reserve (struct radeon_bo*,int) ; 
 int radeon_bo_set_tiling_flags (struct radeon_bo*,int,int) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (struct radeon_bo*) ; 
 int radeon_gem_object_create (struct radeon_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct drm_gem_object**) ; 
 int /*<<< orphan*/  radeonfb_destroy_pinned_object (struct drm_gem_object*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int radeonfb_create_pinned_object(struct radeon_fbdev *rfbdev,
					 struct drm_mode_fb_cmd2 *mode_cmd,
					 struct drm_gem_object **gobj_p)
{
	const struct drm_format_info *info;
	struct radeon_device *rdev = rfbdev->rdev;
	struct drm_gem_object *gobj = NULL;
	struct radeon_bo *rbo = NULL;
	bool fb_tiled = false; /* useful for testing */
	u32 tiling_flags = 0;
	int ret;
	int aligned_size, size;
	int height = mode_cmd->height;
	u32 cpp;

	info = drm_get_format_info(rdev->ddev, mode_cmd);
	cpp = info->cpp[0];

	/* need to align pitch with crtc limits */
	mode_cmd->pitches[0] = radeon_align_pitch(rdev, mode_cmd->width, cpp,
						  fb_tiled);

	if (rdev->family >= CHIP_R600)
		height = ALIGN(mode_cmd->height, 8);
	size = mode_cmd->pitches[0] * height;
	aligned_size = ALIGN(size, PAGE_SIZE);
	ret = radeon_gem_object_create(rdev, aligned_size, 0,
				       RADEON_GEM_DOMAIN_VRAM,
				       0, true, &gobj);
	if (ret) {
		pr_err("failed to allocate framebuffer (%d)\n", aligned_size);
		return -ENOMEM;
	}
	rbo = gem_to_radeon_bo(gobj);

	if (fb_tiled)
		tiling_flags = RADEON_TILING_MACRO;

#ifdef __BIG_ENDIAN
	switch (cpp) {
	case 4:
		tiling_flags |= RADEON_TILING_SWAP_32BIT;
		break;
	case 2:
		tiling_flags |= RADEON_TILING_SWAP_16BIT;
	default:
		break;
	}
#endif

	if (tiling_flags) {
		ret = radeon_bo_set_tiling_flags(rbo,
						 tiling_flags | RADEON_TILING_SURFACE,
						 mode_cmd->pitches[0]);
		if (ret)
			dev_err(rdev->dev, "FB failed to set tiling flags\n");
	}


	ret = radeon_bo_reserve(rbo, false);
	if (unlikely(ret != 0))
		goto out_unref;
	/* Only 27 bit offset for legacy CRTC */
	ret = radeon_bo_pin_restricted(rbo, RADEON_GEM_DOMAIN_VRAM,
				       ASIC_IS_AVIVO(rdev) ? 0 : 1 << 27,
				       NULL);
	if (ret) {
		radeon_bo_unreserve(rbo);
		goto out_unref;
	}
	if (fb_tiled)
		radeon_bo_check_tiling(rbo, 0, 0);
	ret = radeon_bo_kmap(rbo, NULL);
	radeon_bo_unreserve(rbo);
	if (ret) {
		goto out_unref;
	}

	*gobj_p = gobj;
	return 0;
out_unref:
	radeonfb_destroy_pinned_object(gobj);
	*gobj_p = NULL;
	return ret;
}