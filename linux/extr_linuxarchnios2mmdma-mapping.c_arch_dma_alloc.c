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
struct device {int coherent_dma_mask; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_DMA ; 
 void* UNCAC_ADDR (void*) ; 
 int /*<<< orphan*/  __GFP_ZERO ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_dcache_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 int /*<<< orphan*/  virt_to_phys (void*) ; 

void *arch_dma_alloc(struct device *dev, size_t size, dma_addr_t *dma_handle,
		gfp_t gfp, unsigned long attrs)
{
	void *ret;

	/* optimized page clearing */
	gfp |= __GFP_ZERO;

	if (dev == NULL || (dev->coherent_dma_mask < 0xffffffff))
		gfp |= GFP_DMA;

	ret = (void *) __get_free_pages(gfp, get_order(size));
	if (ret != NULL) {
		*dma_handle = virt_to_phys(ret);
		flush_dcache_range((unsigned long) ret,
			(unsigned long) ret + size);
		ret = UNCAC_ADDR(ret);
	}

	return ret;
}