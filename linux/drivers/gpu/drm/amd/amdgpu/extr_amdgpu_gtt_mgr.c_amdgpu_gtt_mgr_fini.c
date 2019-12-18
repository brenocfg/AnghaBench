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
struct ttm_mem_type_manager {struct amdgpu_gtt_mgr* priv; int /*<<< orphan*/  bdev; } ;
struct amdgpu_gtt_mgr {int /*<<< orphan*/  lock; int /*<<< orphan*/  mm; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct amdgpu_device* amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_attr_mem_info_gtt_total ; 
 int /*<<< orphan*/  dev_attr_mem_info_gtt_used ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mm_takedown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct amdgpu_gtt_mgr*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amdgpu_gtt_mgr_fini(struct ttm_mem_type_manager *man)
{
	struct amdgpu_device *adev = amdgpu_ttm_adev(man->bdev);
	struct amdgpu_gtt_mgr *mgr = man->priv;
	spin_lock(&mgr->lock);
	drm_mm_takedown(&mgr->mm);
	spin_unlock(&mgr->lock);
	kfree(mgr);
	man->priv = NULL;

	device_remove_file(adev->dev, &dev_attr_mem_info_gtt_total);
	device_remove_file(adev->dev, &dev_attr_mem_info_gtt_used);

	return 0;
}