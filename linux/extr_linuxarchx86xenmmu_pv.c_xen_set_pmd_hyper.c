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
struct mmu_update {int /*<<< orphan*/  val; int /*<<< orphan*/  ptr; } ;
typedef  int /*<<< orphan*/  pmd_t ;
struct TYPE_2__ {int /*<<< orphan*/  maddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PARAVIRT_LAZY_MMU ; 
 TYPE_1__ arbitrary_virt_to_machine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmd_val_ma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  xen_extend_mmu_update (struct mmu_update*) ; 
 int /*<<< orphan*/  xen_mc_batch () ; 
 int /*<<< orphan*/  xen_mc_issue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xen_set_pmd_hyper(pmd_t *ptr, pmd_t val)
{
	struct mmu_update u;

	preempt_disable();

	xen_mc_batch();

	/* ptr may be ioremapped for 64-bit pagetable setup */
	u.ptr = arbitrary_virt_to_machine(ptr).maddr;
	u.val = pmd_val_ma(val);
	xen_extend_mmu_update(&u);

	xen_mc_issue(PARAVIRT_LAZY_MMU);

	preempt_enable();
}