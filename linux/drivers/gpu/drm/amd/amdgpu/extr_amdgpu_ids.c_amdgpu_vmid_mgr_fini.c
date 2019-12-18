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
struct amdgpu_vmid_mgr {struct amdgpu_vmid* ids; int /*<<< orphan*/  lock; } ;
struct amdgpu_vmid {int /*<<< orphan*/  pasid_mapping; int /*<<< orphan*/  last_flush; int /*<<< orphan*/  flushed_updates; int /*<<< orphan*/  active; } ;
struct TYPE_2__ {struct amdgpu_vmid_mgr* id_mgr; } ;
struct amdgpu_device {TYPE_1__ vm_manager; } ;

/* Variables and functions */
 unsigned int AMDGPU_MAX_VMHUBS ; 
 unsigned int AMDGPU_NUM_VMID ; 
 int /*<<< orphan*/  amdgpu_sync_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void amdgpu_vmid_mgr_fini(struct amdgpu_device *adev)
{
	unsigned i, j;

	for (i = 0; i < AMDGPU_MAX_VMHUBS; ++i) {
		struct amdgpu_vmid_mgr *id_mgr =
			&adev->vm_manager.id_mgr[i];

		mutex_destroy(&id_mgr->lock);
		for (j = 0; j < AMDGPU_NUM_VMID; ++j) {
			struct amdgpu_vmid *id = &id_mgr->ids[j];

			amdgpu_sync_free(&id->active);
			dma_fence_put(id->flushed_updates);
			dma_fence_put(id->last_flush);
			dma_fence_put(id->pasid_mapping);
		}
	}
}