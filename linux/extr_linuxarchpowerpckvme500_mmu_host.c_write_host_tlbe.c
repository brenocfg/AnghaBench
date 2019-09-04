#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {TYPE_3__* kvm; } ;
struct kvmppc_vcpu_e500 {TYPE_2__ vcpu; } ;
struct kvm_book3e_206_tlb_entry {int /*<<< orphan*/  mas2; } ;
struct TYPE_4__ {int /*<<< orphan*/  lpid; } ;
struct TYPE_6__ {TYPE_1__ arch; } ;

/* Variables and functions */
 int MAS0_ESEL (int /*<<< orphan*/ ) ; 
 int MAS0_TLBSEL (int) ; 
 int /*<<< orphan*/  __write_host_tlbe (struct kvm_book3e_206_tlb_entry*,int,int /*<<< orphan*/ ) ; 
 int get_host_mas0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_htlb1_esel (int) ; 

__attribute__((used)) static inline void write_host_tlbe(struct kvmppc_vcpu_e500 *vcpu_e500,
		int tlbsel, int sesel, struct kvm_book3e_206_tlb_entry *stlbe)
{
	u32 mas0;

	if (tlbsel == 0) {
		mas0 = get_host_mas0(stlbe->mas2);
		__write_host_tlbe(stlbe, mas0, vcpu_e500->vcpu.kvm->arch.lpid);
	} else {
		__write_host_tlbe(stlbe,
				  MAS0_TLBSEL(1) |
				  MAS0_ESEL(to_htlb1_esel(sesel)),
				  vcpu_e500->vcpu.kvm->arch.lpid);
	}
}