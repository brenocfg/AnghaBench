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
struct iommu_domain {int dummy; } ;
struct io_pgtable_ops {size_t (* unmap ) (struct io_pgtable_ops*,unsigned long,size_t) ;} ;
struct TYPE_2__ {struct io_pgtable_ops* pgtbl_ops; } ;

/* Variables and functions */
 size_t stub1 (struct io_pgtable_ops*,unsigned long,size_t) ; 
 TYPE_1__* to_smmu_domain (struct iommu_domain*) ; 

__attribute__((used)) static size_t
arm_smmu_unmap(struct iommu_domain *domain, unsigned long iova, size_t size)
{
	struct io_pgtable_ops *ops = to_smmu_domain(domain)->pgtbl_ops;

	if (!ops)
		return 0;

	return ops->unmap(ops, iova, size);
}