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
struct iommu_domain {scalar_t__ type; } ;
struct io_pgtable_ops {int /*<<< orphan*/  (* iova_to_phys ) (struct io_pgtable_ops*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {struct io_pgtable_ops* pgtbl_ops; } ;

/* Variables and functions */
 scalar_t__ IOMMU_DOMAIN_IDENTITY ; 
 int /*<<< orphan*/  stub1 (struct io_pgtable_ops*,int /*<<< orphan*/ ) ; 
 TYPE_1__* to_smmu_domain (struct iommu_domain*) ; 

__attribute__((used)) static phys_addr_t
arm_smmu_iova_to_phys(struct iommu_domain *domain, dma_addr_t iova)
{
	struct io_pgtable_ops *ops = to_smmu_domain(domain)->pgtbl_ops;

	if (domain->type == IOMMU_DOMAIN_IDENTITY)
		return iova;

	if (!ops)
		return 0;

	return ops->iova_to_phys(ops, iova);
}