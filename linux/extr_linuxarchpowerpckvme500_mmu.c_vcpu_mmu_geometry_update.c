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
struct TYPE_2__ {int* tlbcfg; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_book3e_206_tlb_params {int* tlb_sizes; int* tlb_ways; } ;

/* Variables and functions */
 int TLBnCFG_ASSOC ; 
 int TLBnCFG_ASSOC_SHIFT ; 
 int TLBnCFG_N_ENTRY ; 

__attribute__((used)) static int vcpu_mmu_geometry_update(struct kvm_vcpu *vcpu,
		struct kvm_book3e_206_tlb_params *params)
{
	vcpu->arch.tlbcfg[0] &= ~(TLBnCFG_N_ENTRY | TLBnCFG_ASSOC);
	if (params->tlb_sizes[0] <= 2048)
		vcpu->arch.tlbcfg[0] |= params->tlb_sizes[0];
	vcpu->arch.tlbcfg[0] |= params->tlb_ways[0] << TLBnCFG_ASSOC_SHIFT;

	vcpu->arch.tlbcfg[1] &= ~(TLBnCFG_N_ENTRY | TLBnCFG_ASSOC);
	vcpu->arch.tlbcfg[1] |= params->tlb_sizes[1];
	vcpu->arch.tlbcfg[1] |= params->tlb_ways[1] << TLBnCFG_ASSOC_SHIFT;
	return 0;
}