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
struct ttm_mem_type_manager {struct amdgpu_vram_mgr* priv; int /*<<< orphan*/  bdev; } ;
struct amdgpu_vram_mgr {int /*<<< orphan*/  lock; int /*<<< orphan*/  mm; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct amdgpu_device* amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_attr_mem_info_vis_vram_total ; 
 int /*<<< orphan*/  dev_attr_mem_info_vis_vram_used ; 
 int /*<<< orphan*/  dev_attr_mem_info_vram_total ; 
 int /*<<< orphan*/  dev_attr_mem_info_vram_used ; 
 int device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 struct amdgpu_vram_mgr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amdgpu_vram_mgr_init(struct ttm_mem_type_manager *man,
				unsigned long p_size)
{
	struct amdgpu_device *adev = amdgpu_ttm_adev(man->bdev);
	struct amdgpu_vram_mgr *mgr;
	int ret;

	mgr = kzalloc(sizeof(*mgr), GFP_KERNEL);
	if (!mgr)
		return -ENOMEM;

	drm_mm_init(&mgr->mm, 0, p_size);
	spin_lock_init(&mgr->lock);
	man->priv = mgr;

	/* Add the two VRAM-related sysfs files */
	ret = device_create_file(adev->dev, &dev_attr_mem_info_vram_total);
	if (ret) {
		DRM_ERROR("Failed to create device file mem_info_vram_total\n");
		return ret;
	}
	ret = device_create_file(adev->dev, &dev_attr_mem_info_vis_vram_total);
	if (ret) {
		DRM_ERROR("Failed to create device file mem_info_vis_vram_total\n");
		return ret;
	}
	ret = device_create_file(adev->dev, &dev_attr_mem_info_vram_used);
	if (ret) {
		DRM_ERROR("Failed to create device file mem_info_vram_used\n");
		return ret;
	}
	ret = device_create_file(adev->dev, &dev_attr_mem_info_vis_vram_used);
	if (ret) {
		DRM_ERROR("Failed to create device file mem_info_vis_vram_used\n");
		return ret;
	}

	return 0;
}