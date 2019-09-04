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
struct TYPE_2__ {int /*<<< orphan*/  wired_tlb_used; scalar_t__ wired_tlb; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_vz_load_guesttlb (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_vz_vcpu_load_wired(struct kvm_vcpu *vcpu)
{
	/* Load wired entries into the guest TLB */
	if (vcpu->arch.wired_tlb)
		kvm_vz_load_guesttlb(vcpu->arch.wired_tlb, 0,
				     vcpu->arch.wired_tlb_used);
}