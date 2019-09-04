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
struct iommu_domain {int dummy; } ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 int IOMMU_READ ; 
 int IOMMU_WRITE ; 
 int ZPCI_PTE_VALID ; 
 int ZPCI_TABLE_PROTECTED ; 
 int s390_iommu_update_trans (struct s390_domain*,unsigned long,unsigned long,size_t,int) ; 
 struct s390_domain* to_s390_domain (struct iommu_domain*) ; 

__attribute__((used)) static int s390_iommu_map(struct iommu_domain *domain, unsigned long iova,
			  phys_addr_t paddr, size_t size, int prot)
{
	struct s390_domain *s390_domain = to_s390_domain(domain);
	int flags = ZPCI_PTE_VALID, rc = 0;

	if (!(prot & IOMMU_READ))
		return -EINVAL;

	if (!(prot & IOMMU_WRITE))
		flags |= ZPCI_TABLE_PROTECTED;

	rc = s390_iommu_update_trans(s390_domain, (unsigned long) paddr, iova,
				     size, flags);

	return rc;
}