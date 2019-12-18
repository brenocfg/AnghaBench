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
struct TYPE_4__ {int quirks; } ;
struct TYPE_3__ {scalar_t__ fmt; TYPE_2__ cfg; } ;
struct arm_lpae_io_pgtable {TYPE_1__ iop; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  arm_lpae_iopte ;

/* Variables and functions */
 int ARM_LPAE_MAX_LEVELS ; 
 int /*<<< orphan*/  ARM_LPAE_PTE_AF ; 
 int /*<<< orphan*/  ARM_LPAE_PTE_NS ; 
 int /*<<< orphan*/  ARM_LPAE_PTE_SH_IS ; 
 int /*<<< orphan*/  ARM_LPAE_PTE_TYPE_BLOCK ; 
 int /*<<< orphan*/  ARM_LPAE_PTE_TYPE_PAGE ; 
 scalar_t__ ARM_MALI_LPAE ; 
 int IO_PGTABLE_QUIRK_ARM_NS ; 
 int /*<<< orphan*/  __arm_lpae_set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  paddr_to_iopte (int /*<<< orphan*/ ,struct arm_lpae_io_pgtable*) ; 

__attribute__((used)) static void __arm_lpae_init_pte(struct arm_lpae_io_pgtable *data,
				phys_addr_t paddr, arm_lpae_iopte prot,
				int lvl, arm_lpae_iopte *ptep)
{
	arm_lpae_iopte pte = prot;

	if (data->iop.cfg.quirks & IO_PGTABLE_QUIRK_ARM_NS)
		pte |= ARM_LPAE_PTE_NS;

	if (data->iop.fmt != ARM_MALI_LPAE && lvl == ARM_LPAE_MAX_LEVELS - 1)
		pte |= ARM_LPAE_PTE_TYPE_PAGE;
	else
		pte |= ARM_LPAE_PTE_TYPE_BLOCK;

	if (data->iop.fmt != ARM_MALI_LPAE)
		pte |= ARM_LPAE_PTE_AF;
	pte |= ARM_LPAE_PTE_SH_IS;
	pte |= paddr_to_iopte(paddr, data);

	__arm_lpae_set_pte(ptep, pte, &data->iop.cfg);
}