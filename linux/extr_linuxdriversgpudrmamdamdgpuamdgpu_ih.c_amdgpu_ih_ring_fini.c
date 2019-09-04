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
struct TYPE_3__ {int /*<<< orphan*/  rptr_offs; int /*<<< orphan*/  wptr_offs; int /*<<< orphan*/ * ring; int /*<<< orphan*/  gpu_addr; int /*<<< orphan*/  ring_obj; int /*<<< orphan*/  rb_dma_addr; scalar_t__ ring_size; scalar_t__ use_bus_addr; } ;
struct TYPE_4__ {TYPE_1__ ih; } ;
struct amdgpu_device {TYPE_2__ irq; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  amdgpu_device_wb_free (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,scalar_t__,void*,int /*<<< orphan*/ ) ; 

void amdgpu_ih_ring_fini(struct amdgpu_device *adev)
{
	if (adev->irq.ih.use_bus_addr) {
		if (adev->irq.ih.ring) {
			/* add 8 bytes for the rptr/wptr shadows and
			 * add them to the end of the ring allocation.
			 */
			pci_free_consistent(adev->pdev, adev->irq.ih.ring_size + 8,
					    (void *)adev->irq.ih.ring,
					    adev->irq.ih.rb_dma_addr);
			adev->irq.ih.ring = NULL;
		}
	} else {
		amdgpu_bo_free_kernel(&adev->irq.ih.ring_obj,
				      &adev->irq.ih.gpu_addr,
				      (void **)&adev->irq.ih.ring);
		amdgpu_device_wb_free(adev, adev->irq.ih.wptr_offs);
		amdgpu_device_wb_free(adev, adev->irq.ih.rptr_offs);
	}
}