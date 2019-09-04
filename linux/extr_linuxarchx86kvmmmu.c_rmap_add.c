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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
struct kvm_rmap_head {int dummy; } ;
struct kvm_mmu_page {int spt; } ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ *) ; 
 struct kvm_rmap_head* gfn_to_rmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kvm_mmu_page*) ; 
 int /*<<< orphan*/  kvm_mmu_page_set_gfn (struct kvm_mmu_page*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct kvm_mmu_page* page_header (int /*<<< orphan*/ ) ; 
 int pte_list_add (struct kvm_vcpu*,int /*<<< orphan*/ *,struct kvm_rmap_head*) ; 

__attribute__((used)) static int rmap_add(struct kvm_vcpu *vcpu, u64 *spte, gfn_t gfn)
{
	struct kvm_mmu_page *sp;
	struct kvm_rmap_head *rmap_head;

	sp = page_header(__pa(spte));
	kvm_mmu_page_set_gfn(sp, spte - sp->spt, gfn);
	rmap_head = gfn_to_rmap(vcpu->kvm, gfn, sp);
	return pte_list_add(vcpu, spte, rmap_head);
}