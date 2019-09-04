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
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* iova_to_phys ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct ipmmu_vmsa_domain* to_vmsa_domain (struct iommu_domain*) ; 

__attribute__((used)) static phys_addr_t ipmmu_iova_to_phys(struct iommu_domain *io_domain,
				      dma_addr_t iova)
{
	struct ipmmu_vmsa_domain *domain = to_vmsa_domain(io_domain);

	/* TODO: Is locking needed ? */

	return domain->iop->iova_to_phys(domain->iop, iova);
}