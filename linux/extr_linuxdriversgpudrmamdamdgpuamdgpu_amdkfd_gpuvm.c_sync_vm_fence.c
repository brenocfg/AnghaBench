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
struct dma_fence {int dummy; } ;
struct amdgpu_sync {int /*<<< orphan*/ * last_vm_update; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int amdgpu_sync_fence (struct amdgpu_device*,struct amdgpu_sync*,struct dma_fence*,int) ; 
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sync_vm_fence(struct amdgpu_device *adev, struct amdgpu_sync *sync,
			 struct dma_fence *f)
{
	int ret = amdgpu_sync_fence(adev, sync, f, false);

	/* Sync objects can't handle multiple GPUs (contexts) updating
	 * sync->last_vm_update. Fortunately we don't need it for
	 * KFD's purposes, so we can just drop that fence.
	 */
	if (sync->last_vm_update) {
		dma_fence_put(sync->last_vm_update);
		sync->last_vm_update = NULL;
	}

	return ret;
}