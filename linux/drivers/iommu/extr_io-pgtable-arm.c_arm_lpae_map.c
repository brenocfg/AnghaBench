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
struct io_pgtable_ops {int dummy; } ;
struct TYPE_3__ {unsigned long long ias; unsigned long long oas; } ;
struct TYPE_4__ {TYPE_1__ cfg; } ;
struct arm_lpae_io_pgtable {TYPE_2__ iop; int /*<<< orphan*/ * pgd; } ;
typedef  unsigned long long phys_addr_t ;
typedef  int /*<<< orphan*/  arm_lpae_iopte ;

/* Variables and functions */
 int ARM_LPAE_START_LVL (struct arm_lpae_io_pgtable*) ; 
 int ERANGE ; 
 int IOMMU_READ ; 
 int IOMMU_WRITE ; 
 scalar_t__ WARN_ON (int) ; 
 int __arm_lpae_map (struct arm_lpae_io_pgtable*,unsigned long,unsigned long long,size_t,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arm_lpae_prot_to_pte (struct arm_lpae_io_pgtable*,int) ; 
 struct arm_lpae_io_pgtable* io_pgtable_ops_to_data (struct io_pgtable_ops*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int arm_lpae_map(struct io_pgtable_ops *ops, unsigned long iova,
			phys_addr_t paddr, size_t size, int iommu_prot)
{
	struct arm_lpae_io_pgtable *data = io_pgtable_ops_to_data(ops);
	arm_lpae_iopte *ptep = data->pgd;
	int ret, lvl = ARM_LPAE_START_LVL(data);
	arm_lpae_iopte prot;

	/* If no access, then nothing to do */
	if (!(iommu_prot & (IOMMU_READ | IOMMU_WRITE)))
		return 0;

	if (WARN_ON(iova >= (1ULL << data->iop.cfg.ias) ||
		    paddr >= (1ULL << data->iop.cfg.oas)))
		return -ERANGE;

	prot = arm_lpae_prot_to_pte(data, iommu_prot);
	ret = __arm_lpae_map(data, iova, paddr, size, prot, lvl, ptep);
	/*
	 * Synchronise all PTE updates for the new mapping before there's
	 * a chance for anything to kick off a table walk for the new iova.
	 */
	wmb();

	return ret;
}