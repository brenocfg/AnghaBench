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
typedef  int phys_addr_t ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int XEN_PAGE_MASK ; 
 int XEN_PAGE_SHIFT ; 
 int /*<<< orphan*/  XEN_PFN_DOWN (int) ; 
 unsigned long bfn_to_pfn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline phys_addr_t xen_bus_to_phys(dma_addr_t baddr)
{
	unsigned long xen_pfn = bfn_to_pfn(XEN_PFN_DOWN(baddr));
	dma_addr_t dma = (dma_addr_t)xen_pfn << XEN_PAGE_SHIFT;
	phys_addr_t paddr = dma;

	paddr |= baddr & ~XEN_PAGE_MASK;

	return paddr;
}