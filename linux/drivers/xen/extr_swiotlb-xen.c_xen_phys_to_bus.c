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
 unsigned long pfn_to_bfn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline dma_addr_t xen_phys_to_bus(phys_addr_t paddr)
{
	unsigned long bfn = pfn_to_bfn(XEN_PFN_DOWN(paddr));
	dma_addr_t dma = (dma_addr_t)bfn << XEN_PAGE_SHIFT;

	dma |= paddr & ~XEN_PAGE_MASK;

	return dma;
}