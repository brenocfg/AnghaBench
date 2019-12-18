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
struct s390_domain {int dummy; } ;
struct iommu_iotlb_gather {int dummy; } ;
struct iommu_domain {int dummy; } ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 int ZPCI_PTE_INVALID ; 
 scalar_t__ s390_iommu_iova_to_phys (struct iommu_domain*,unsigned long) ; 
 int s390_iommu_update_trans (struct s390_domain*,unsigned long,unsigned long,size_t,int) ; 
 struct s390_domain* to_s390_domain (struct iommu_domain*) ; 

__attribute__((used)) static size_t s390_iommu_unmap(struct iommu_domain *domain,
			       unsigned long iova, size_t size,
			       struct iommu_iotlb_gather *gather)
{
	struct s390_domain *s390_domain = to_s390_domain(domain);
	int flags = ZPCI_PTE_INVALID;
	phys_addr_t paddr;
	int rc;

	paddr = s390_iommu_iova_to_phys(domain, iova);
	if (!paddr)
		return 0;

	rc = s390_iommu_update_trans(s390_domain, (unsigned long) paddr, iova,
				     size, flags);
	if (rc)
		return 0;

	return size;
}