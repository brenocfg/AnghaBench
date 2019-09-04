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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 size_t PAGE_ALIGN (size_t) ; 
 scalar_t__ __free_from_pool (void*,size_t) ; 
 int /*<<< orphan*/  dma_to_phys (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_device_dma_coherent (struct device*) ; 
 void* phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swiotlb_free (struct device*,size_t,void*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  vunmap (void*) ; 

__attribute__((used)) static void __dma_free(struct device *dev, size_t size,
		       void *vaddr, dma_addr_t dma_handle,
		       unsigned long attrs)
{
	void *swiotlb_addr = phys_to_virt(dma_to_phys(dev, dma_handle));

	size = PAGE_ALIGN(size);

	if (!is_device_dma_coherent(dev)) {
		if (__free_from_pool(vaddr, size))
			return;
		vunmap(vaddr);
	}
	swiotlb_free(dev, size, swiotlb_addr, dma_handle, attrs);
}