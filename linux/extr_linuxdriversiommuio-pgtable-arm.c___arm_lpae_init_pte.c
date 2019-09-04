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
struct TYPE_3__ {TYPE_2__ cfg; } ;
struct arm_lpae_io_pgtable {TYPE_1__ iop; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int arm_lpae_iopte ;

/* Variables and functions */
 int ARM_LPAE_MAX_LEVELS ; 
 int ARM_LPAE_PTE_AF ; 
 int ARM_LPAE_PTE_NS ; 
 int ARM_LPAE_PTE_SH_IS ; 
 int ARM_LPAE_PTE_TYPE_BLOCK ; 
 int ARM_LPAE_PTE_TYPE_PAGE ; 
 int IO_PGTABLE_QUIRK_ARM_NS ; 
 int /*<<< orphan*/  __arm_lpae_set_pte (int*,int,TYPE_2__*) ; 
 int paddr_to_iopte (int /*<<< orphan*/ ,struct arm_lpae_io_pgtable*) ; 

__attribute__((used)) static void __arm_lpae_init_pte(struct arm_lpae_io_pgtable *data,
				phys_addr_t paddr, arm_lpae_iopte prot,
				int lvl, arm_lpae_iopte *ptep)
{
	arm_lpae_iopte pte = prot;

	if (data->iop.cfg.quirks & IO_PGTABLE_QUIRK_ARM_NS)
		pte |= ARM_LPAE_PTE_NS;

	if (lvl == ARM_LPAE_MAX_LEVELS - 1)
		pte |= ARM_LPAE_PTE_TYPE_PAGE;
	else
		pte |= ARM_LPAE_PTE_TYPE_BLOCK;

	pte |= ARM_LPAE_PTE_AF | ARM_LPAE_PTE_SH_IS;
	pte |= paddr_to_iopte(paddr, data);

	__arm_lpae_set_pte(ptep, pte, &data->iop.cfg);
}