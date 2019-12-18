#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ttm_buffer_object {int /*<<< orphan*/  bdev; } ;
struct amdgpu_device {int /*<<< orphan*/  shadow_list_lock; } ;
struct TYPE_5__ {scalar_t__ import_attach; } ;
struct TYPE_4__ {TYPE_2__ base; int /*<<< orphan*/  sg; } ;
struct amdgpu_bo {scalar_t__ pin_count; struct amdgpu_bo* metadata; int /*<<< orphan*/  parent; int /*<<< orphan*/  shadow_list; TYPE_1__ tbo; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_kunmap (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_bo_subtract_pin_size (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_bo_unref (int /*<<< orphan*/ *) ; 
 struct amdgpu_device* amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_release (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_prime_gem_destroy (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct amdgpu_bo* ttm_to_amdgpu_bo (struct ttm_buffer_object*) ; 

__attribute__((used)) static void amdgpu_bo_destroy(struct ttm_buffer_object *tbo)
{
	struct amdgpu_device *adev = amdgpu_ttm_adev(tbo->bdev);
	struct amdgpu_bo *bo = ttm_to_amdgpu_bo(tbo);

	if (bo->pin_count > 0)
		amdgpu_bo_subtract_pin_size(bo);

	amdgpu_bo_kunmap(bo);

	if (bo->tbo.base.import_attach)
		drm_prime_gem_destroy(&bo->tbo.base, bo->tbo.sg);
	drm_gem_object_release(&bo->tbo.base);
	/* in case amdgpu_device_recover_vram got NULL of bo->parent */
	if (!list_empty(&bo->shadow_list)) {
		mutex_lock(&adev->shadow_list_lock);
		list_del_init(&bo->shadow_list);
		mutex_unlock(&adev->shadow_list_lock);
	}
	amdgpu_bo_unref(&bo->parent);

	kfree(bo->metadata);
	kfree(bo);
}