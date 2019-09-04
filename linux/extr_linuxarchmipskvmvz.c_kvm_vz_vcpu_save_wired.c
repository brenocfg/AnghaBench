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
struct TYPE_2__ {unsigned int wired_tlb_limit; int wired_tlb_used; struct kvm_mips_tlb* wired_tlb; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_mips_tlb {scalar_t__ tlb_mask; scalar_t__* tlb_lo; int /*<<< orphan*/  tlb_hi; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned int MIPSR6_WIRED_WIRED ; 
 int /*<<< orphan*/  UNIQUE_GUEST_ENTRYHI (int) ; 
 scalar_t__ WARN_ON (int) ; 
 struct kvm_mips_tlb* krealloc (struct kvm_mips_tlb*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_vz_save_guesttlb (struct kvm_mips_tlb*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int read_gc0_wired () ; 

__attribute__((used)) static void kvm_vz_vcpu_save_wired(struct kvm_vcpu *vcpu)
{
	unsigned int wired = read_gc0_wired();
	struct kvm_mips_tlb *tlbs;
	int i;

	/* Expand the wired TLB array if necessary */
	wired &= MIPSR6_WIRED_WIRED;
	if (wired > vcpu->arch.wired_tlb_limit) {
		tlbs = krealloc(vcpu->arch.wired_tlb, wired *
				sizeof(*vcpu->arch.wired_tlb), GFP_ATOMIC);
		if (WARN_ON(!tlbs)) {
			/* Save whatever we can */
			wired = vcpu->arch.wired_tlb_limit;
		} else {
			vcpu->arch.wired_tlb = tlbs;
			vcpu->arch.wired_tlb_limit = wired;
		}
	}

	if (wired)
		/* Save wired entries from the guest TLB */
		kvm_vz_save_guesttlb(vcpu->arch.wired_tlb, 0, wired);
	/* Invalidate any dropped entries since last time */
	for (i = wired; i < vcpu->arch.wired_tlb_used; ++i) {
		vcpu->arch.wired_tlb[i].tlb_hi = UNIQUE_GUEST_ENTRYHI(i);
		vcpu->arch.wired_tlb[i].tlb_lo[0] = 0;
		vcpu->arch.wired_tlb[i].tlb_lo[1] = 0;
		vcpu->arch.wired_tlb[i].tlb_mask = 0;
	}
	vcpu->arch.wired_tlb_used = wired;
}