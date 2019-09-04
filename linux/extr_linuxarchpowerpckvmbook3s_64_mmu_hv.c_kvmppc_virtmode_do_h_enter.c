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
struct kvm {int dummy; } ;
struct TYPE_4__ {TYPE_1__* mm; } ;
struct TYPE_3__ {int /*<<< orphan*/  pgd; } ;

/* Variables and functions */
 long H_RESOURCE ; 
 long H_TOO_HARD ; 
 TYPE_2__* current ; 
 long kvmppc_do_h_enter (struct kvm*,unsigned long,long,unsigned long,unsigned long,int /*<<< orphan*/ ,int,unsigned long*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  rcu_read_lock_sched () ; 
 int /*<<< orphan*/  rcu_read_unlock_sched () ; 

__attribute__((used)) static long kvmppc_virtmode_do_h_enter(struct kvm *kvm, unsigned long flags,
				long pte_index, unsigned long pteh,
				unsigned long ptel, unsigned long *pte_idx_ret)
{
	long ret;

	/* Protect linux PTE lookup from page table destruction */
	rcu_read_lock_sched();	/* this disables preemption too */
	ret = kvmppc_do_h_enter(kvm, flags, pte_index, pteh, ptel,
				current->mm->pgd, false, pte_idx_ret);
	rcu_read_unlock_sched();
	if (ret == H_TOO_HARD) {
		/* this can't happen */
		pr_err("KVM: Oops, kvmppc_h_enter returned too hard!\n");
		ret = H_RESOURCE;	/* or something */
	}
	return ret;

}