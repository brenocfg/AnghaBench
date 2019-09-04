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
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 void* dma_alloc_from_global_coherent (size_t,int /*<<< orphan*/ *) ; 
 void* dma_direct_alloc (struct device*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void *arm_nommu_dma_alloc(struct device *dev, size_t size,
				 dma_addr_t *dma_handle, gfp_t gfp,
				 unsigned long attrs)

{
	void *ret;

	/*
	 * Try generic allocator first if we are advertised that
	 * consistency is not required.
	 */

	if (attrs & DMA_ATTR_NON_CONSISTENT)
		return dma_direct_alloc(dev, size, dma_handle, gfp, attrs);

	ret = dma_alloc_from_global_coherent(size, dma_handle);

	/*
	 * dma_alloc_from_global_coherent() may fail because:
	 *
	 * - no consistent DMA region has been defined, so we can't
	 *   continue.
	 * - there is no space left in consistent DMA region, so we
	 *   only can fallback to generic allocator if we are
	 *   advertised that consistency is not required.
	 */

	WARN_ON_ONCE(ret == NULL);
	return ret;
}