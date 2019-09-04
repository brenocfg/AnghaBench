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
struct kvm_vcpu {int dummy; } ;
struct kvm_mmu {int root_level; int shadow_root_level; int direct_map; int /*<<< orphan*/  update_pte; int /*<<< orphan*/  invlpg; int /*<<< orphan*/  sync_page; int /*<<< orphan*/  gva_to_gpa; int /*<<< orphan*/  page_fault; int /*<<< orphan*/  nx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_WARN_ON (int) ; 
 int /*<<< orphan*/  is_nx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_pae (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  paging64_gva_to_gpa ; 
 int /*<<< orphan*/  paging64_invlpg ; 
 int /*<<< orphan*/  paging64_page_fault ; 
 int /*<<< orphan*/  paging64_sync_page ; 
 int /*<<< orphan*/  paging64_update_pte ; 
 int /*<<< orphan*/  reset_rsvds_bits_mask (struct kvm_vcpu*,struct kvm_mmu*) ; 
 int /*<<< orphan*/  update_last_nonleaf_level (struct kvm_vcpu*,struct kvm_mmu*) ; 
 int /*<<< orphan*/  update_permission_bitmask (struct kvm_vcpu*,struct kvm_mmu*,int) ; 
 int /*<<< orphan*/  update_pkru_bitmask (struct kvm_vcpu*,struct kvm_mmu*,int) ; 

__attribute__((used)) static void paging64_init_context_common(struct kvm_vcpu *vcpu,
					 struct kvm_mmu *context,
					 int level)
{
	context->nx = is_nx(vcpu);
	context->root_level = level;

	reset_rsvds_bits_mask(vcpu, context);
	update_permission_bitmask(vcpu, context, false);
	update_pkru_bitmask(vcpu, context, false);
	update_last_nonleaf_level(vcpu, context);

	MMU_WARN_ON(!is_pae(vcpu));
	context->page_fault = paging64_page_fault;
	context->gva_to_gpa = paging64_gva_to_gpa;
	context->sync_page = paging64_sync_page;
	context->invlpg = paging64_invlpg;
	context->update_pte = paging64_update_pte;
	context->shadow_root_level = level;
	context->direct_map = false;
}