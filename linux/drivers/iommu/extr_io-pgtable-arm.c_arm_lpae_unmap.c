#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iommu_iotlb_gather {int dummy; } ;
struct io_pgtable_ops {int dummy; } ;
struct TYPE_3__ {unsigned long long ias; } ;
struct TYPE_4__ {TYPE_1__ cfg; } ;
struct arm_lpae_io_pgtable {TYPE_2__ iop; int /*<<< orphan*/ * pgd; } ;
typedef  int /*<<< orphan*/  arm_lpae_iopte ;

/* Variables and functions */
 int ARM_LPAE_START_LVL (struct arm_lpae_io_pgtable*) ; 
 scalar_t__ WARN_ON (int) ; 
 size_t __arm_lpae_unmap (struct arm_lpae_io_pgtable*,struct iommu_iotlb_gather*,unsigned long,size_t,int,int /*<<< orphan*/ *) ; 
 struct arm_lpae_io_pgtable* io_pgtable_ops_to_data (struct io_pgtable_ops*) ; 

__attribute__((used)) static size_t arm_lpae_unmap(struct io_pgtable_ops *ops, unsigned long iova,
			     size_t size, struct iommu_iotlb_gather *gather)
{
	struct arm_lpae_io_pgtable *data = io_pgtable_ops_to_data(ops);
	arm_lpae_iopte *ptep = data->pgd;
	int lvl = ARM_LPAE_START_LVL(data);

	if (WARN_ON(iova >= (1ULL << data->iop.cfg.ias)))
		return 0;

	return __arm_lpae_unmap(data, gather, iova, size, lvl, ptep);
}