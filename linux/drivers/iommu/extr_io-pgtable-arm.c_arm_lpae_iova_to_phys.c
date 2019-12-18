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
struct TYPE_2__ {int /*<<< orphan*/  fmt; } ;
struct arm_lpae_io_pgtable {TYPE_1__ iop; int /*<<< orphan*/ * pgd; } ;
typedef  unsigned long phys_addr_t ;
typedef  int /*<<< orphan*/  arm_lpae_iopte ;

/* Variables and functions */
 int ARM_LPAE_BLOCK_SIZE (int,struct arm_lpae_io_pgtable*) ; 
 int /*<<< orphan*/  ARM_LPAE_LVL_IDX (unsigned long,int,struct arm_lpae_io_pgtable*) ; 
 int ARM_LPAE_MAX_LEVELS ; 
 int ARM_LPAE_START_LVL (struct arm_lpae_io_pgtable*) ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 struct arm_lpae_io_pgtable* io_pgtable_ops_to_data (struct io_pgtable_ops*) ; 
 int /*<<< orphan*/ * iopte_deref (int /*<<< orphan*/ ,struct arm_lpae_io_pgtable*) ; 
 scalar_t__ iopte_leaf (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 unsigned long iopte_to_paddr (int /*<<< orphan*/ ,struct arm_lpae_io_pgtable*) ; 

__attribute__((used)) static phys_addr_t arm_lpae_iova_to_phys(struct io_pgtable_ops *ops,
					 unsigned long iova)
{
	struct arm_lpae_io_pgtable *data = io_pgtable_ops_to_data(ops);
	arm_lpae_iopte pte, *ptep = data->pgd;
	int lvl = ARM_LPAE_START_LVL(data);

	do {
		/* Valid IOPTE pointer? */
		if (!ptep)
			return 0;

		/* Grab the IOPTE we're interested in */
		ptep += ARM_LPAE_LVL_IDX(iova, lvl, data);
		pte = READ_ONCE(*ptep);

		/* Valid entry? */
		if (!pte)
			return 0;

		/* Leaf entry? */
		if (iopte_leaf(pte, lvl, data->iop.fmt))
			goto found_translation;

		/* Take it to the next level */
		ptep = iopte_deref(pte, data);
	} while (++lvl < ARM_LPAE_MAX_LEVELS);

	/* Ran out of page tables to walk */
	return 0;

found_translation:
	iova &= (ARM_LPAE_BLOCK_SIZE(lvl, data) - 1);
	return iopte_to_paddr(pte, data) | iova;
}