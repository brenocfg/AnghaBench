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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct drm_mode_fb_cmd2 {int height; int* pitches; int /*<<< orphan*/  width; } ;
struct drm_gem_object {int dummy; } ;
struct drm_format_info {scalar_t__* cpp; } ;
struct amdgpu_fbdev {struct amdgpu_device* adev; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  ddev; } ;
struct amdgpu_bo {int /*<<< orphan*/  tbo; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED ; 
 int AMDGPU_GEM_CREATE_CPU_GTT_USWC ; 
 int AMDGPU_GEM_CREATE_VRAM_CLEARED ; 
 int AMDGPU_GEM_CREATE_VRAM_CONTIGUOUS ; 
 scalar_t__ AMDGPU_TILING_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARRAY_MODE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GRPH_ARRAY_2D_TILED_THIN1 ; 
 int PAGE_SIZE ; 
 int amdgpu_align_pitch (struct amdgpu_device*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int amdgpu_bo_kmap (struct amdgpu_bo*,int /*<<< orphan*/ *) ; 
 int amdgpu_bo_pin (struct amdgpu_bo*,scalar_t__) ; 
 int amdgpu_bo_reserve (struct amdgpu_bo*,int) ; 
 int amdgpu_bo_set_tiling_flags (struct amdgpu_bo*,scalar_t__) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (struct amdgpu_bo*) ; 
 scalar_t__ amdgpu_display_supported_domains (struct amdgpu_device*,int) ; 
 int amdgpu_gem_object_create (struct amdgpu_device*,int,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct drm_gem_object**) ; 
 int amdgpu_ttm_alloc_gart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpufb_destroy_pinned_object (struct drm_gem_object*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct drm_format_info* drm_get_format_info (int /*<<< orphan*/ ,struct drm_mode_fb_cmd2*) ; 
 struct amdgpu_bo* gem_to_amdgpu_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  ttm_bo_type_kernel ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int amdgpufb_create_pinned_object(struct amdgpu_fbdev *rfbdev,
					 struct drm_mode_fb_cmd2 *mode_cmd,
					 struct drm_gem_object **gobj_p)
{
	const struct drm_format_info *info;
	struct amdgpu_device *adev = rfbdev->adev;
	struct drm_gem_object *gobj = NULL;
	struct amdgpu_bo *abo = NULL;
	bool fb_tiled = false; /* useful for testing */
	u32 tiling_flags = 0, domain;
	int ret;
	int aligned_size, size;
	int height = mode_cmd->height;
	u32 cpp;
	u64 flags = AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED |
			       AMDGPU_GEM_CREATE_VRAM_CONTIGUOUS     |
			       AMDGPU_GEM_CREATE_VRAM_CLEARED 	     |
			       AMDGPU_GEM_CREATE_CPU_GTT_USWC;

	info = drm_get_format_info(adev->ddev, mode_cmd);
	cpp = info->cpp[0];

	/* need to align pitch with crtc limits */
	mode_cmd->pitches[0] = amdgpu_align_pitch(adev, mode_cmd->width, cpp,
						  fb_tiled);
	domain = amdgpu_display_supported_domains(adev, flags);
	height = ALIGN(mode_cmd->height, 8);
	size = mode_cmd->pitches[0] * height;
	aligned_size = ALIGN(size, PAGE_SIZE);
	ret = amdgpu_gem_object_create(adev, aligned_size, 0, domain, flags,
				       ttm_bo_type_kernel, NULL, &gobj);
	if (ret) {
		pr_err("failed to allocate framebuffer (%d)\n", aligned_size);
		return -ENOMEM;
	}
	abo = gem_to_amdgpu_bo(gobj);

	if (fb_tiled)
		tiling_flags = AMDGPU_TILING_SET(ARRAY_MODE, GRPH_ARRAY_2D_TILED_THIN1);

	ret = amdgpu_bo_reserve(abo, false);
	if (unlikely(ret != 0))
		goto out_unref;

	if (tiling_flags) {
		ret = amdgpu_bo_set_tiling_flags(abo,
						 tiling_flags);
		if (ret)
			dev_err(adev->dev, "FB failed to set tiling flags\n");
	}

	ret = amdgpu_bo_pin(abo, domain);
	if (ret) {
		amdgpu_bo_unreserve(abo);
		goto out_unref;
	}

	ret = amdgpu_ttm_alloc_gart(&abo->tbo);
	if (ret) {
		amdgpu_bo_unreserve(abo);
		dev_err(adev->dev, "%p bind failed\n", abo);
		goto out_unref;
	}

	ret = amdgpu_bo_kmap(abo, NULL);
	amdgpu_bo_unreserve(abo);
	if (ret) {
		goto out_unref;
	}

	*gobj_p = gobj;
	return 0;
out_unref:
	amdgpufb_destroy_pinned_object(gobj);
	*gobj_p = NULL;
	return ret;
}