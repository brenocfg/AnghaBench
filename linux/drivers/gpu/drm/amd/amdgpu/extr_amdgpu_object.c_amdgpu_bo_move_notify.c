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
struct ttm_mem_reg {int /*<<< orphan*/  mem_type; } ;
struct ttm_buffer_object {struct ttm_mem_reg mem; int /*<<< orphan*/  bdev; } ;
struct amdgpu_device {int /*<<< orphan*/  num_evictions; } ;
struct amdgpu_bo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_is_amdgpu_bo (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  amdgpu_bo_kunmap (struct amdgpu_bo*) ; 
 struct amdgpu_device* amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_vm_bo_invalidate (struct amdgpu_device*,struct amdgpu_bo*,int) ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_amdgpu_bo_move (struct amdgpu_bo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct amdgpu_bo* ttm_to_amdgpu_bo (struct ttm_buffer_object*) ; 

void amdgpu_bo_move_notify(struct ttm_buffer_object *bo,
			   bool evict,
			   struct ttm_mem_reg *new_mem)
{
	struct amdgpu_device *adev = amdgpu_ttm_adev(bo->bdev);
	struct amdgpu_bo *abo;
	struct ttm_mem_reg *old_mem = &bo->mem;

	if (!amdgpu_bo_is_amdgpu_bo(bo))
		return;

	abo = ttm_to_amdgpu_bo(bo);
	amdgpu_vm_bo_invalidate(adev, abo, evict);

	amdgpu_bo_kunmap(abo);

	/* remember the eviction */
	if (evict)
		atomic64_inc(&adev->num_evictions);

	/* update statistics */
	if (!new_mem)
		return;

	/* move_notify is called before move happens */
	trace_amdgpu_bo_move(abo, new_mem->mem_type, old_mem->mem_type);
}