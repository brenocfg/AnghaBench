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
typedef  int /*<<< orphan*/  u64 ;
struct nicvf {scalar_t__ iommu_domain; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  iommu_iova_to_phys (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 nicvf_iova_to_phys(struct nicvf *nic, dma_addr_t dma_addr)
{
	/* Translation is installed only when IOMMU is present */
	if (nic->iommu_domain)
		return iommu_iova_to_phys(nic->iommu_domain, dma_addr);
	return dma_addr;
}