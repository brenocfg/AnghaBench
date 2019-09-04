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
typedef  int ulong ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kvmppc_mmu_pte_flush_all (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_mmu_pte_flush_long (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvmppc_mmu_pte_flush_page (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  trace_kvm_book3s_mmu_flush (char*,struct kvm_vcpu*,int,int) ; 

void kvmppc_mmu_pte_flush(struct kvm_vcpu *vcpu, ulong guest_ea, ulong ea_mask)
{
	trace_kvm_book3s_mmu_flush("", vcpu, guest_ea, ea_mask);
	guest_ea &= ea_mask;

	switch (ea_mask) {
	case ~0xfffUL:
		kvmppc_mmu_pte_flush_page(vcpu, guest_ea);
		break;
	case 0x0ffff000:
		kvmppc_mmu_pte_flush_long(vcpu, guest_ea);
		break;
	case 0:
		/* Doing a complete flush -> start from scratch */
		kvmppc_mmu_pte_flush_all(vcpu);
		break;
	default:
		WARN_ON(1);
		break;
	}
}