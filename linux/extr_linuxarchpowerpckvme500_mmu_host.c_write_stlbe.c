#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kvmppc_vcpu_e500 {int /*<<< orphan*/  vcpu; } ;
struct kvm_book3e_206_tlb_entry {int /*<<< orphan*/  mas1; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAS1_TID (int) ; 
 int kvmppc_e500_get_tlb_stid (int /*<<< orphan*/ *,struct kvm_book3e_206_tlb_entry*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  write_host_tlbe (struct kvmppc_vcpu_e500*,int,int,struct kvm_book3e_206_tlb_entry*) ; 

__attribute__((used)) static void write_stlbe(struct kvmppc_vcpu_e500 *vcpu_e500,
			struct kvm_book3e_206_tlb_entry *gtlbe,
			struct kvm_book3e_206_tlb_entry *stlbe,
			int stlbsel, int sesel)
{
	int stid;

	preempt_disable();
	stid = kvmppc_e500_get_tlb_stid(&vcpu_e500->vcpu, gtlbe);

	stlbe->mas1 |= MAS1_TID(stid);
	write_host_tlbe(vcpu_e500, stlbsel, sesel, stlbe);
	preempt_enable();
}