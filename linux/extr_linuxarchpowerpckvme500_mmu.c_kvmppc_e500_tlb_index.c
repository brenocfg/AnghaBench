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
struct kvmppc_vcpu_e500 {scalar_t__ tlb1_min_eaddr; scalar_t__ tlb1_max_eaddr; unsigned int* gtlb_offset; struct kvm_book3e_206_tlb_entry* gtlb_arch; TYPE_1__* gtlb_params; } ;
struct kvm_book3e_206_tlb_entry {int dummy; } ;
typedef  scalar_t__ gva_t ;
struct TYPE_2__ {int entries; int ways; } ;

/* Variables and functions */
 scalar_t__ get_tlb_eaddr (struct kvm_book3e_206_tlb_entry*) ; 
 scalar_t__ get_tlb_end (struct kvm_book3e_206_tlb_entry*) ; 
 unsigned int get_tlb_tid (struct kvm_book3e_206_tlb_entry*) ; 
 int get_tlb_ts (struct kvm_book3e_206_tlb_entry*) ; 
 int /*<<< orphan*/  get_tlb_v (struct kvm_book3e_206_tlb_entry*) ; 
 unsigned int gtlb0_set_base (struct kvmppc_vcpu_e500*,scalar_t__) ; 

__attribute__((used)) static int kvmppc_e500_tlb_index(struct kvmppc_vcpu_e500 *vcpu_e500,
		gva_t eaddr, int tlbsel, unsigned int pid, int as)
{
	int size = vcpu_e500->gtlb_params[tlbsel].entries;
	unsigned int set_base, offset;
	int i;

	if (tlbsel == 0) {
		set_base = gtlb0_set_base(vcpu_e500, eaddr);
		size = vcpu_e500->gtlb_params[0].ways;
	} else {
		if (eaddr < vcpu_e500->tlb1_min_eaddr ||
				eaddr > vcpu_e500->tlb1_max_eaddr)
			return -1;
		set_base = 0;
	}

	offset = vcpu_e500->gtlb_offset[tlbsel];

	for (i = 0; i < size; i++) {
		struct kvm_book3e_206_tlb_entry *tlbe =
			&vcpu_e500->gtlb_arch[offset + set_base + i];
		unsigned int tid;

		if (eaddr < get_tlb_eaddr(tlbe))
			continue;

		if (eaddr > get_tlb_end(tlbe))
			continue;

		tid = get_tlb_tid(tlbe);
		if (tid && (tid != pid))
			continue;

		if (!get_tlb_v(tlbe))
			continue;

		if (get_tlb_ts(tlbe) != as && as != -1)
			continue;

		return set_base + i;
	}

	return -1;
}