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
typedef  int u32 ;
struct TYPE_3__ {unsigned int ring_size; int ptr_mask; int use_bus_addr; int wptr_offs; int rptr_offs; int /*<<< orphan*/ * ring; int /*<<< orphan*/  rb_dma_addr; scalar_t__ rptr; } ;
struct TYPE_4__ {TYPE_1__ ih; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; TYPE_2__ irq; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  amdgpu_device_wb_free (struct amdgpu_device*,int) ; 
 int amdgpu_device_wb_get (struct amdgpu_device*,int*) ; 
 int amdgpu_ih_ring_alloc (struct amdgpu_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int order_base_2 (unsigned int) ; 
 int /*<<< orphan*/ * pci_alloc_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int amdgpu_ih_ring_init(struct amdgpu_device *adev, unsigned ring_size,
			bool use_bus_addr)
{
	u32 rb_bufsz;
	int r;

	/* Align ring size */
	rb_bufsz = order_base_2(ring_size / 4);
	ring_size = (1 << rb_bufsz) * 4;
	adev->irq.ih.ring_size = ring_size;
	adev->irq.ih.ptr_mask = adev->irq.ih.ring_size - 1;
	adev->irq.ih.rptr = 0;
	adev->irq.ih.use_bus_addr = use_bus_addr;

	if (adev->irq.ih.use_bus_addr) {
		if (!adev->irq.ih.ring) {
			/* add 8 bytes for the rptr/wptr shadows and
			 * add them to the end of the ring allocation.
			 */
			adev->irq.ih.ring = pci_alloc_consistent(adev->pdev,
								 adev->irq.ih.ring_size + 8,
								 &adev->irq.ih.rb_dma_addr);
			if (adev->irq.ih.ring == NULL)
				return -ENOMEM;
			memset((void *)adev->irq.ih.ring, 0, adev->irq.ih.ring_size + 8);
			adev->irq.ih.wptr_offs = (adev->irq.ih.ring_size / 4) + 0;
			adev->irq.ih.rptr_offs = (adev->irq.ih.ring_size / 4) + 1;
		}
		return 0;
	} else {
		r = amdgpu_device_wb_get(adev, &adev->irq.ih.wptr_offs);
		if (r) {
			dev_err(adev->dev, "(%d) ih wptr_offs wb alloc failed\n", r);
			return r;
		}

		r = amdgpu_device_wb_get(adev, &adev->irq.ih.rptr_offs);
		if (r) {
			amdgpu_device_wb_free(adev, adev->irq.ih.wptr_offs);
			dev_err(adev->dev, "(%d) ih rptr_offs wb alloc failed\n", r);
			return r;
		}

		return amdgpu_ih_ring_alloc(adev);
	}
}