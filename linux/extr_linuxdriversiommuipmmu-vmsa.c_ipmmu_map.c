#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ipmmu_vmsa_domain {TYPE_1__* iop; } ;
struct iommu_domain {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
struct TYPE_2__ {int (* map ) (TYPE_1__*,unsigned long,int /*<<< orphan*/ ,size_t,int) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int stub1 (TYPE_1__*,unsigned long,int /*<<< orphan*/ ,size_t,int) ; 
 struct ipmmu_vmsa_domain* to_vmsa_domain (struct iommu_domain*) ; 

__attribute__((used)) static int ipmmu_map(struct iommu_domain *io_domain, unsigned long iova,
		     phys_addr_t paddr, size_t size, int prot)
{
	struct ipmmu_vmsa_domain *domain = to_vmsa_domain(io_domain);

	if (!domain)
		return -ENODEV;

	return domain->iop->map(domain->iop, iova, paddr, size, prot);
}