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
struct TYPE_4__ {int slb_nr; TYPE_1__* slb; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_3__ {int valid; scalar_t__ origv; scalar_t__ orige; } ;

/* Variables and functions */
 int MSR_IR ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int kvmppc_get_msr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_pc (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_mmu_flush_segments (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_mmu_map_segment (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvmppc_mmu_book3s_64_slbia(struct kvm_vcpu *vcpu)
{
	int i;

	dprintk("KVM MMU: slbia()\n");

	for (i = 1; i < vcpu->arch.slb_nr; i++) {
		vcpu->arch.slb[i].valid = false;
		vcpu->arch.slb[i].orige = 0;
		vcpu->arch.slb[i].origv = 0;
	}

	if (kvmppc_get_msr(vcpu) & MSR_IR) {
		kvmppc_mmu_flush_segments(vcpu);
		kvmppc_mmu_map_segment(vcpu, kvmppc_get_pc(vcpu));
	}
}