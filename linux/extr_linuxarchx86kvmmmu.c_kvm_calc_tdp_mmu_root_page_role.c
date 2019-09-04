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
union kvm_mmu_page_role {int ad_disabled; int direct; int /*<<< orphan*/  access; int /*<<< orphan*/  level; int /*<<< orphan*/  smm; int /*<<< orphan*/  guest_mode; int /*<<< orphan*/  member_0; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_tdp_level ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ACC_ALL ; 
 int /*<<< orphan*/  is_guest_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_smm (struct kvm_vcpu*) ; 
 TYPE_1__* kvm_x86_ops ; 
 scalar_t__ shadow_accessed_mask ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*) ; 

__attribute__((used)) static union kvm_mmu_page_role
kvm_calc_tdp_mmu_root_page_role(struct kvm_vcpu *vcpu)
{
	union kvm_mmu_page_role role = {0};

	role.guest_mode = is_guest_mode(vcpu);
	role.smm = is_smm(vcpu);
	role.ad_disabled = (shadow_accessed_mask == 0);
	role.level = kvm_x86_ops->get_tdp_level(vcpu);
	role.direct = true;
	role.access = ACC_ALL;

	return role;
}