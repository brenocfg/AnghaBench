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
struct ntb_transport_mw {scalar_t__ alloc_size; scalar_t__ buff_size; int /*<<< orphan*/  dma_addr; void* virt_addr; void* alloc_addr; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,size_t) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ALIGNED (int /*<<< orphan*/ ,size_t) ; 
 void* PTR_ALIGN (void*,size_t) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__) ; 
 void* dma_alloc_coherent (struct device*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,scalar_t__,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ntb_alloc_mw_buffer(struct ntb_transport_mw *mw,
			       struct device *dma_dev, size_t align)
{
	dma_addr_t dma_addr;
	void *alloc_addr, *virt_addr;
	int rc;

	alloc_addr = dma_alloc_coherent(dma_dev, mw->alloc_size,
					&dma_addr, GFP_KERNEL);
	if (!alloc_addr) {
		dev_err(dma_dev, "Unable to alloc MW buff of size %zu\n",
			mw->alloc_size);
		return -ENOMEM;
	}
	virt_addr = alloc_addr;

	/*
	 * we must ensure that the memory address allocated is BAR size
	 * aligned in order for the XLAT register to take the value. This
	 * is a requirement of the hardware. It is recommended to setup CMA
	 * for BAR sizes equal or greater than 4MB.
	 */
	if (!IS_ALIGNED(dma_addr, align)) {
		if (mw->alloc_size > mw->buff_size) {
			virt_addr = PTR_ALIGN(alloc_addr, align);
			dma_addr = ALIGN(dma_addr, align);
		} else {
			rc = -ENOMEM;
			goto err;
		}
	}

	mw->alloc_addr = alloc_addr;
	mw->virt_addr = virt_addr;
	mw->dma_addr = dma_addr;

	return 0;

err:
	dma_free_coherent(dma_dev, mw->alloc_size, alloc_addr, dma_addr);

	return rc;
}