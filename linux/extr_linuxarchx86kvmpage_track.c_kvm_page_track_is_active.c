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
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** gfn_track; } ;
struct kvm_memory_slot {TYPE_1__ arch; int /*<<< orphan*/  base_gfn; } ;
typedef  int /*<<< orphan*/  gfn_t ;
typedef  enum kvm_page_track_mode { ____Placeholder_kvm_page_track_mode } kvm_page_track_mode ;

/* Variables and functions */
 int /*<<< orphan*/  PT_PAGE_TABLE_LEVEL ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int gfn_to_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct kvm_memory_slot* kvm_vcpu_gfn_to_memslot (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_track_mode_is_valid (int) ; 

bool kvm_page_track_is_active(struct kvm_vcpu *vcpu, gfn_t gfn,
			      enum kvm_page_track_mode mode)
{
	struct kvm_memory_slot *slot;
	int index;

	if (WARN_ON(!page_track_mode_is_valid(mode)))
		return false;

	slot = kvm_vcpu_gfn_to_memslot(vcpu, gfn);
	if (!slot)
		return false;

	index = gfn_to_index(gfn, slot->base_gfn, PT_PAGE_TABLE_LEVEL);
	return !!READ_ONCE(slot->arch.gfn_track[mode][index]);
}