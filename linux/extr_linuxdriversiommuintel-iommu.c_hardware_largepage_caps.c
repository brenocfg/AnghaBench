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
struct dmar_domain {int iommu_superpage; } ;

/* Variables and functions */
 unsigned long VTD_STRIDE_MASK ; 
 unsigned long VTD_STRIDE_SHIFT ; 

__attribute__((used)) static inline int hardware_largepage_caps(struct dmar_domain *domain,
					  unsigned long iov_pfn,
					  unsigned long phy_pfn,
					  unsigned long pages)
{
	int support, level = 1;
	unsigned long pfnmerge;

	support = domain->iommu_superpage;

	/* To use a large page, the virtual *and* physical addresses
	   must be aligned to 2MiB/1GiB/etc. Lower bits set in either
	   of them will mean we have to use smaller pages. So just
	   merge them and check both at once. */
	pfnmerge = iov_pfn | phy_pfn;

	while (support && !(pfnmerge & ~VTD_STRIDE_MASK)) {
		pages >>= VTD_STRIDE_SHIFT;
		if (!pages)
			break;
		pfnmerge >>= VTD_STRIDE_SHIFT;
		level++;
		support--;
	}
	return level;
}