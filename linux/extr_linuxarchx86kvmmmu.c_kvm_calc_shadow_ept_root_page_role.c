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
union kvm_mmu_page_role {int direct; int ad_disabled; int guest_mode; int /*<<< orphan*/  access; int /*<<< orphan*/  level; } ;
struct TYPE_3__ {union kvm_mmu_page_role base_role; } ;
struct TYPE_4__ {TYPE_1__ mmu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACC_ALL ; 
 int /*<<< orphan*/  PT64_ROOT_4LEVEL ; 

__attribute__((used)) static union kvm_mmu_page_role
kvm_calc_shadow_ept_root_page_role(struct kvm_vcpu *vcpu, bool accessed_dirty)
{
	union kvm_mmu_page_role role = vcpu->arch.mmu.base_role;

	role.level = PT64_ROOT_4LEVEL;
	role.direct = false;
	role.ad_disabled = !accessed_dirty;
	role.guest_mode = true;
	role.access = ACC_ALL;

	return role;
}