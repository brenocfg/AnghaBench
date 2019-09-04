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
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned long DMA_ATTR_NON_CONSISTENT ; 
 scalar_t__ UNCAC_ADDR (void*) ; 
 int /*<<< orphan*/  VDMA_ERROR ; 
 int /*<<< orphan*/  dma_cache_wback_inv (unsigned long,size_t) ; 
 void* dma_direct_alloc (struct device*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dma_direct_free (struct device*,size_t,void*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  vdma_alloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  virt_to_phys (void*) ; 

__attribute__((used)) static void *jazz_dma_alloc(struct device *dev, size_t size,
		dma_addr_t *dma_handle, gfp_t gfp, unsigned long attrs)
{
	void *ret;

	ret = dma_direct_alloc(dev, size, dma_handle, gfp, attrs);
	if (!ret)
		return NULL;

	*dma_handle = vdma_alloc(virt_to_phys(ret), size);
	if (*dma_handle == VDMA_ERROR) {
		dma_direct_free(dev, size, ret, *dma_handle, attrs);
		return NULL;
	}

	if (!(attrs & DMA_ATTR_NON_CONSISTENT)) {
		dma_cache_wback_inv((unsigned long)ret, size);
		ret = (void *)UNCAC_ADDR(ret);
	}
	return ret;
}