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
struct iommu_domain {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  iommu_iova_to_phys (struct iommu_domain*,int /*<<< orphan*/ ) ; 
 void* phys_to_virt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *dpaa2_iova_to_virt(struct iommu_domain *domain,
				dma_addr_t iova_addr)
{
	phys_addr_t phys_addr;

	phys_addr = domain ? iommu_iova_to_phys(domain, iova_addr) : iova_addr;

	return phys_to_virt(phys_addr);
}