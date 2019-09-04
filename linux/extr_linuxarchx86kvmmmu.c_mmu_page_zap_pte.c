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
typedef  int u64 ;
struct TYPE_3__ {int /*<<< orphan*/  level; } ;
struct kvm_mmu_page {TYPE_1__ role; } ;
struct TYPE_4__ {int /*<<< orphan*/  lpages; } ;
struct kvm {TYPE_2__ stat; } ;

/* Variables and functions */
 int PT64_BASE_ADDR_MASK ; 
 int /*<<< orphan*/  drop_parent_pte (struct kvm_mmu_page*,int*) ; 
 int /*<<< orphan*/  drop_spte (struct kvm*,int*) ; 
 scalar_t__ is_large_pte (int) ; 
 scalar_t__ is_last_spte (int,int /*<<< orphan*/ ) ; 
 scalar_t__ is_mmio_spte (int) ; 
 scalar_t__ is_shadow_present_pte (int) ; 
 int /*<<< orphan*/  mmu_spte_clear_no_track (int*) ; 
 struct kvm_mmu_page* page_header (int) ; 

__attribute__((used)) static bool mmu_page_zap_pte(struct kvm *kvm, struct kvm_mmu_page *sp,
			     u64 *spte)
{
	u64 pte;
	struct kvm_mmu_page *child;

	pte = *spte;
	if (is_shadow_present_pte(pte)) {
		if (is_last_spte(pte, sp->role.level)) {
			drop_spte(kvm, spte);
			if (is_large_pte(pte))
				--kvm->stat.lpages;
		} else {
			child = page_header(pte & PT64_BASE_ADDR_MASK);
			drop_parent_pte(child, spte);
		}
		return true;
	}

	if (is_mmio_spte(pte))
		mmu_spte_clear_no_track(spte);

	return false;
}