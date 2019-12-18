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
typedef  scalar_t__ phys_addr_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int IO_TLB_SEGSIZE ; 
 int IO_TLB_SHIFT ; 
 int /*<<< orphan*/  MAX_DMA_BITS ; 
 int PAGE_SHIFT ; 
 int get_order (int) ; 
 int min (unsigned long,unsigned long) ; 
 scalar_t__ virt_to_phys (void*) ; 
 int xen_create_contiguous_region (scalar_t__,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xen_swiotlb_fixup(void *buf, size_t size, unsigned long nslabs)
{
	int i, rc;
	int dma_bits;
	dma_addr_t dma_handle;
	phys_addr_t p = virt_to_phys(buf);

	dma_bits = get_order(IO_TLB_SEGSIZE << IO_TLB_SHIFT) + PAGE_SHIFT;

	i = 0;
	do {
		int slabs = min(nslabs - i, (unsigned long)IO_TLB_SEGSIZE);

		do {
			rc = xen_create_contiguous_region(
				p + (i << IO_TLB_SHIFT),
				get_order(slabs << IO_TLB_SHIFT),
				dma_bits, &dma_handle);
		} while (rc && dma_bits++ < MAX_DMA_BITS);
		if (rc)
			return rc;

		i += slabs;
	} while (i < nslabs);
	return 0;
}