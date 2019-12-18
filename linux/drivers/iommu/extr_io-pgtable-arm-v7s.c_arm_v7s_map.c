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
struct io_pgtable_ops {int dummy; } ;
struct TYPE_2__ {unsigned long long ias; unsigned long long oas; int quirks; } ;
struct io_pgtable {TYPE_1__ cfg; } ;
struct arm_v7s_io_pgtable {int /*<<< orphan*/  pgd; struct io_pgtable iop; } ;
typedef  unsigned long long phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_V7S_BLOCK_SIZE (int) ; 
 int ERANGE ; 
 int IOMMU_READ ; 
 int IOMMU_WRITE ; 
 int IO_PGTABLE_QUIRK_TLBI_ON_MAP ; 
 scalar_t__ WARN_ON (int) ; 
 int __arm_v7s_map (struct arm_v7s_io_pgtable*,unsigned long,unsigned long long,size_t,int,int,int /*<<< orphan*/ ) ; 
 struct arm_v7s_io_pgtable* io_pgtable_ops_to_data (struct io_pgtable_ops*) ; 
 int /*<<< orphan*/  io_pgtable_tlb_flush_walk (struct io_pgtable*,unsigned long,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int arm_v7s_map(struct io_pgtable_ops *ops, unsigned long iova,
			phys_addr_t paddr, size_t size, int prot)
{
	struct arm_v7s_io_pgtable *data = io_pgtable_ops_to_data(ops);
	struct io_pgtable *iop = &data->iop;
	int ret;

	/* If no access, then nothing to do */
	if (!(prot & (IOMMU_READ | IOMMU_WRITE)))
		return 0;

	if (WARN_ON(iova >= (1ULL << data->iop.cfg.ias) ||
		    paddr >= (1ULL << data->iop.cfg.oas)))
		return -ERANGE;

	ret = __arm_v7s_map(data, iova, paddr, size, prot, 1, data->pgd);
	/*
	 * Synchronise all PTE updates for the new mapping before there's
	 * a chance for anything to kick off a table walk for the new iova.
	 */
	if (iop->cfg.quirks & IO_PGTABLE_QUIRK_TLBI_ON_MAP) {
		io_pgtable_tlb_flush_walk(iop, iova, size,
					  ARM_V7S_BLOCK_SIZE(2));
	} else {
		wmb();
	}

	return ret;
}