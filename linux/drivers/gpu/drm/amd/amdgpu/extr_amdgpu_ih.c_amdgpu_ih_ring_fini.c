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
struct amdgpu_ih_ring {int gpu_addr; int wptr_addr; int rptr_addr; int /*<<< orphan*/ * ring; int /*<<< orphan*/  ring_obj; scalar_t__ ring_size; scalar_t__ use_bus_addr; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int*,void**) ; 
 int /*<<< orphan*/  amdgpu_device_wb_free (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,scalar_t__,void*,int) ; 

void amdgpu_ih_ring_fini(struct amdgpu_device *adev, struct amdgpu_ih_ring *ih)
{
	if (ih->use_bus_addr) {
		if (!ih->ring)
			return;

		/* add 8 bytes for the rptr/wptr shadows and
		 * add them to the end of the ring allocation.
		 */
		dma_free_coherent(adev->dev, ih->ring_size + 8,
				  (void *)ih->ring, ih->gpu_addr);
		ih->ring = NULL;
	} else {
		amdgpu_bo_free_kernel(&ih->ring_obj, &ih->gpu_addr,
				      (void **)&ih->ring);
		amdgpu_device_wb_free(adev, (ih->wptr_addr - ih->gpu_addr) / 4);
		amdgpu_device_wb_free(adev, (ih->rptr_addr - ih->gpu_addr) / 4);
	}
}