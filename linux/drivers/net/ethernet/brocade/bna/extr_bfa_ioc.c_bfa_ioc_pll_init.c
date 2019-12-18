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
struct TYPE_2__ {int /*<<< orphan*/  ioc_init_sem_reg; } ;
struct bfa_ioc {int pllinit; TYPE_1__ ioc_regs; } ;
typedef  enum bfa_status { ____Placeholder_bfa_status } bfa_status ;

/* Variables and functions */
 int BFA_STATUS_OK ; 
 int /*<<< orphan*/  bfa_ioc_lmem_init (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_ioc_pll_init_asic (struct bfa_ioc*) ; 
 int /*<<< orphan*/  bfa_nw_ioc_sem_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_nw_ioc_sem_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum bfa_status
bfa_ioc_pll_init(struct bfa_ioc *ioc)
{
	/*
	 *  Hold semaphore so that nobody can access the chip during init.
	 */
	bfa_nw_ioc_sem_get(ioc->ioc_regs.ioc_init_sem_reg);

	bfa_ioc_pll_init_asic(ioc);

	ioc->pllinit = true;

	/* Initialize LMEM */
	bfa_ioc_lmem_init(ioc);

	/*
	 *  release semaphore.
	 */
	bfa_nw_ioc_sem_release(ioc->ioc_regs.ioc_init_sem_reg);

	return BFA_STATUS_OK;
}