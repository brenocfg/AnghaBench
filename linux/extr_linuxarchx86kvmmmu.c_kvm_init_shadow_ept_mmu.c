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
union kvm_mmu_page_role {int word; } ;
struct TYPE_5__ {int word; } ;
struct kvm_mmu {int nx; int ept_ad; int direct_map; TYPE_2__ base_role; void* root_level; int /*<<< orphan*/  update_pte; int /*<<< orphan*/  invlpg; int /*<<< orphan*/  sync_page; int /*<<< orphan*/  gva_to_gpa; int /*<<< orphan*/  page_fault; void* shadow_root_level; } ;
struct TYPE_4__ {struct kvm_mmu mmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  gpa_t ;
struct TYPE_6__ {int word; } ;

/* Variables and functions */
 void* PT64_ROOT_4LEVEL ; 
 int /*<<< orphan*/  __kvm_mmu_new_cr3 (struct kvm_vcpu*,int /*<<< orphan*/ ,union kvm_mmu_page_role,int) ; 
 int /*<<< orphan*/  ept_gva_to_gpa ; 
 int /*<<< orphan*/  ept_invlpg ; 
 int /*<<< orphan*/  ept_page_fault ; 
 int /*<<< orphan*/  ept_sync_page ; 
 int /*<<< orphan*/  ept_update_pte ; 
 union kvm_mmu_page_role kvm_calc_shadow_ept_root_page_role (struct kvm_vcpu*,int) ; 
 TYPE_3__ mmu_base_role_mask ; 
 int /*<<< orphan*/  reset_ept_shadow_zero_bits_mask (struct kvm_vcpu*,struct kvm_mmu*,int) ; 
 int /*<<< orphan*/  reset_rsvds_bits_mask_ept (struct kvm_vcpu*,struct kvm_mmu*,int) ; 
 int /*<<< orphan*/  update_last_nonleaf_level (struct kvm_vcpu*,struct kvm_mmu*) ; 
 int /*<<< orphan*/  update_permission_bitmask (struct kvm_vcpu*,struct kvm_mmu*,int) ; 
 int /*<<< orphan*/  update_pkru_bitmask (struct kvm_vcpu*,struct kvm_mmu*,int) ; 

void kvm_init_shadow_ept_mmu(struct kvm_vcpu *vcpu, bool execonly,
			     bool accessed_dirty, gpa_t new_eptp)
{
	struct kvm_mmu *context = &vcpu->arch.mmu;
	union kvm_mmu_page_role root_page_role =
		kvm_calc_shadow_ept_root_page_role(vcpu, accessed_dirty);

	__kvm_mmu_new_cr3(vcpu, new_eptp, root_page_role, false);
	context->shadow_root_level = PT64_ROOT_4LEVEL;

	context->nx = true;
	context->ept_ad = accessed_dirty;
	context->page_fault = ept_page_fault;
	context->gva_to_gpa = ept_gva_to_gpa;
	context->sync_page = ept_sync_page;
	context->invlpg = ept_invlpg;
	context->update_pte = ept_update_pte;
	context->root_level = PT64_ROOT_4LEVEL;
	context->direct_map = false;
	context->base_role.word = root_page_role.word & mmu_base_role_mask.word;
	update_permission_bitmask(vcpu, context, true);
	update_pkru_bitmask(vcpu, context, true);
	update_last_nonleaf_level(vcpu, context);
	reset_rsvds_bits_mask_ept(vcpu, context, execonly);
	reset_ept_shadow_zero_bits_mask(vcpu, context, execonly);
}