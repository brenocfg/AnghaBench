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
typedef  union kvm_mmu_page_role {int dummy; } kvm_mmu_page_role ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 union kvm_mmu_page_role kvm_calc_shadow_mmu_root_page_role (struct kvm_vcpu*) ; 
 union kvm_mmu_page_role kvm_calc_tdp_mmu_root_page_role (struct kvm_vcpu*) ; 
 scalar_t__ tdp_enabled ; 

__attribute__((used)) static union kvm_mmu_page_role
kvm_mmu_calc_root_page_role(struct kvm_vcpu *vcpu)
{
	if (tdp_enabled)
		return kvm_calc_tdp_mmu_root_page_role(vcpu);
	else
		return kvm_calc_shadow_mmu_root_page_role(vcpu);
}