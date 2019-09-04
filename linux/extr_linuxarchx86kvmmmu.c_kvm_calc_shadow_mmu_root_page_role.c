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
union kvm_mmu_page_role {int cr4_pae; int smep_andnot_wp; int smap_andnot_wp; int direct; int /*<<< orphan*/  level; int /*<<< orphan*/  access; int /*<<< orphan*/  smm; int /*<<< orphan*/  guest_mode; int /*<<< orphan*/  cr0_wp; int /*<<< orphan*/  nxe; int /*<<< orphan*/  member_0; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACC_ALL ; 
 int /*<<< orphan*/  PT32E_ROOT_LEVEL ; 
 int /*<<< orphan*/  PT64_ROOT_4LEVEL ; 
 int /*<<< orphan*/  PT64_ROOT_5LEVEL ; 
 int /*<<< orphan*/  X86_CR4_SMAP ; 
 int /*<<< orphan*/  X86_CR4_SMEP ; 
 int /*<<< orphan*/  is_guest_mode (struct kvm_vcpu*) ; 
 scalar_t__ is_la57_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_long_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_nx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_pae (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_paging (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_smm (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_write_protection (struct kvm_vcpu*) ; 
 int kvm_read_cr4_bits (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static union kvm_mmu_page_role
kvm_calc_shadow_mmu_root_page_role(struct kvm_vcpu *vcpu)
{
	union kvm_mmu_page_role role = {0};
	bool smep = kvm_read_cr4_bits(vcpu, X86_CR4_SMEP);
	bool smap = kvm_read_cr4_bits(vcpu, X86_CR4_SMAP);

	role.nxe = is_nx(vcpu);
	role.cr4_pae = !!is_pae(vcpu);
	role.cr0_wp  = is_write_protection(vcpu);
	role.smep_andnot_wp = smep && !is_write_protection(vcpu);
	role.smap_andnot_wp = smap && !is_write_protection(vcpu);
	role.guest_mode = is_guest_mode(vcpu);
	role.smm = is_smm(vcpu);
	role.direct = !is_paging(vcpu);
	role.access = ACC_ALL;

	if (!is_long_mode(vcpu))
		role.level = PT32E_ROOT_LEVEL;
	else if (is_la57_mode(vcpu))
		role.level = PT64_ROOT_5LEVEL;
	else
		role.level = PT64_ROOT_4LEVEL;

	return role;
}