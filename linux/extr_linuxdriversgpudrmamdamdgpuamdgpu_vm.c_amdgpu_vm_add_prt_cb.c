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
struct dma_fence {int dummy; } ;
struct amdgpu_prt_cb {int /*<<< orphan*/  cb; struct amdgpu_device* adev; } ;
struct TYPE_4__ {TYPE_1__* gmc_funcs; } ;
struct amdgpu_device {TYPE_2__ gmc; } ;
struct TYPE_3__ {int /*<<< orphan*/  set_prt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  amdgpu_vm_prt_cb (struct dma_fence*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_vm_prt_put (struct amdgpu_device*) ; 
 scalar_t__ dma_fence_add_callback (struct dma_fence*,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (struct dma_fence*,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  dma_fence_wait (struct dma_fence*,int) ; 
 struct amdgpu_prt_cb* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void amdgpu_vm_add_prt_cb(struct amdgpu_device *adev,
				 struct dma_fence *fence)
{
	struct amdgpu_prt_cb *cb;

	if (!adev->gmc.gmc_funcs->set_prt)
		return;

	cb = kmalloc(sizeof(struct amdgpu_prt_cb), GFP_KERNEL);
	if (!cb) {
		/* Last resort when we are OOM */
		if (fence)
			dma_fence_wait(fence, false);

		amdgpu_vm_prt_put(adev);
	} else {
		cb->adev = adev;
		if (!fence || dma_fence_add_callback(fence, &cb->cb,
						     amdgpu_vm_prt_cb))
			amdgpu_vm_prt_cb(fence, &cb->cb);
	}
}