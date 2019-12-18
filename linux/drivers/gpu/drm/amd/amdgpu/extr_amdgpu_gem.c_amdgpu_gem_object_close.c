#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ww_acquire_ctx {int dummy; } ;
struct ttm_validate_buffer {int num_shared; int /*<<< orphan*/  head; TYPE_1__* bo; } ;
struct list_head {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_file {struct amdgpu_fpriv* driver_priv; } ;
struct dma_fence {int dummy; } ;
struct amdgpu_vm {int dummy; } ;
struct amdgpu_fpriv {struct amdgpu_vm vm; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; } ;
struct amdgpu_bo_va {scalar_t__ ref_count; } ;
struct amdgpu_bo_list_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;
struct amdgpu_bo {TYPE_1__ tbo; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  amdgpu_bo_fence (struct amdgpu_bo*,struct dma_fence*,int) ; 
 struct amdgpu_device* amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 
 struct amdgpu_bo_va* amdgpu_vm_bo_find (struct amdgpu_vm*,struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_vm_bo_rmv (struct amdgpu_device*,struct amdgpu_bo_va*) ; 
 int amdgpu_vm_clear_freed (struct amdgpu_device*,struct amdgpu_vm*,struct dma_fence**) ; 
 int /*<<< orphan*/  amdgpu_vm_get_pd_bo (struct amdgpu_vm*,struct list_head*,struct amdgpu_bo_list_entry*) ; 
 scalar_t__ amdgpu_vm_ready (struct amdgpu_vm*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 struct amdgpu_bo* gem_to_amdgpu_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  ttm_eu_backoff_reservation (struct ww_acquire_ctx*,struct list_head*) ; 
 int ttm_eu_reserve_buffers (struct ww_acquire_ctx*,struct list_head*,int,struct list_head*,int) ; 
 scalar_t__ unlikely (int) ; 

void amdgpu_gem_object_close(struct drm_gem_object *obj,
			     struct drm_file *file_priv)
{
	struct amdgpu_bo *bo = gem_to_amdgpu_bo(obj);
	struct amdgpu_device *adev = amdgpu_ttm_adev(bo->tbo.bdev);
	struct amdgpu_fpriv *fpriv = file_priv->driver_priv;
	struct amdgpu_vm *vm = &fpriv->vm;

	struct amdgpu_bo_list_entry vm_pd;
	struct list_head list, duplicates;
	struct ttm_validate_buffer tv;
	struct ww_acquire_ctx ticket;
	struct amdgpu_bo_va *bo_va;
	int r;

	INIT_LIST_HEAD(&list);
	INIT_LIST_HEAD(&duplicates);

	tv.bo = &bo->tbo;
	tv.num_shared = 1;
	list_add(&tv.head, &list);

	amdgpu_vm_get_pd_bo(vm, &list, &vm_pd);

	r = ttm_eu_reserve_buffers(&ticket, &list, false, &duplicates, false);
	if (r) {
		dev_err(adev->dev, "leaking bo va because "
			"we fail to reserve bo (%d)\n", r);
		return;
	}
	bo_va = amdgpu_vm_bo_find(vm, bo);
	if (bo_va && --bo_va->ref_count == 0) {
		amdgpu_vm_bo_rmv(adev, bo_va);

		if (amdgpu_vm_ready(vm)) {
			struct dma_fence *fence = NULL;

			r = amdgpu_vm_clear_freed(adev, vm, &fence);
			if (unlikely(r)) {
				dev_err(adev->dev, "failed to clear page "
					"tables on GEM object close (%d)\n", r);
			}

			if (fence) {
				amdgpu_bo_fence(bo, fence, true);
				dma_fence_put(fence);
			}
		}
	}
	ttm_eu_backoff_reservation(&ticket, &list);
}