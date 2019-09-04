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
struct TYPE_2__ {scalar_t__ level; } ;
struct kvm_mmu_page {int /*<<< orphan*/ * spt; TYPE_1__ role; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int PT64_ENT_PER_PAGE ; 
 scalar_t__ PT_PAGE_TABLE_LEVEL ; 
 int /*<<< orphan*/  inspect_spte_has_rmap (struct kvm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_shadow_present_pte (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_mappings_rmap(struct kvm *kvm, struct kvm_mmu_page *sp)
{
	int i;

	if (sp->role.level != PT_PAGE_TABLE_LEVEL)
		return;

	for (i = 0; i < PT64_ENT_PER_PAGE; ++i) {
		if (!is_shadow_present_pte(sp->spt[i]))
			continue;

		inspect_spte_has_rmap(kvm, sp->spt + i);
	}
}