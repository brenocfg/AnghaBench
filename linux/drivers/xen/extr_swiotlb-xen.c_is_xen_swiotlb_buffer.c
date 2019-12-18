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
 int /*<<< orphan*/  PFN_DOWN (scalar_t__) ; 
 unsigned long XEN_PFN_DOWN (int /*<<< orphan*/ ) ; 
 scalar_t__ XEN_PFN_PHYS (unsigned long) ; 
 unsigned long bfn_to_local_pfn (unsigned long) ; 
 scalar_t__ pfn_valid (int /*<<< orphan*/ ) ; 
 scalar_t__ virt_to_phys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_io_tlb_end ; 
 int /*<<< orphan*/  xen_io_tlb_start ; 

__attribute__((used)) static int is_xen_swiotlb_buffer(dma_addr_t dma_addr)
{
	unsigned long bfn = XEN_PFN_DOWN(dma_addr);
	unsigned long xen_pfn = bfn_to_local_pfn(bfn);
	phys_addr_t paddr = XEN_PFN_PHYS(xen_pfn);

	/* If the address is outside our domain, it CAN
	 * have the same virtual address as another address
	 * in our domain. Therefore _only_ check address within our domain.
	 */
	if (pfn_valid(PFN_DOWN(paddr))) {
		return paddr >= virt_to_phys(xen_io_tlb_start) &&
		       paddr < virt_to_phys(xen_io_tlb_end);
	}
	return 0;
}