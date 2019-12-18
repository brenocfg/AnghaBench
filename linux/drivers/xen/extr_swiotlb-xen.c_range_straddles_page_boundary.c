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
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 unsigned long XEN_PFN_DOWN (int /*<<< orphan*/ ) ; 
 unsigned int XEN_PFN_UP (scalar_t__) ; 
 unsigned long pfn_to_bfn (unsigned long) ; 
 scalar_t__ xen_offset_in_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int range_straddles_page_boundary(phys_addr_t p, size_t size)
{
	unsigned long next_bfn, xen_pfn = XEN_PFN_DOWN(p);
	unsigned int i, nr_pages = XEN_PFN_UP(xen_offset_in_page(p) + size);

	next_bfn = pfn_to_bfn(xen_pfn);

	for (i = 1; i < nr_pages; i++)
		if (pfn_to_bfn(++xen_pfn) != ++next_bfn)
			return 1;

	return 0;
}