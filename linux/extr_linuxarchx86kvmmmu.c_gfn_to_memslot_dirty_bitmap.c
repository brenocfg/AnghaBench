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
struct kvm_memory_slot {int dummy; } ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 struct kvm_memory_slot* kvm_vcpu_gfn_to_memslot (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memslot_valid_for_gpte (struct kvm_memory_slot*,int) ; 

__attribute__((used)) static struct kvm_memory_slot *
gfn_to_memslot_dirty_bitmap(struct kvm_vcpu *vcpu, gfn_t gfn,
			    bool no_dirty_log)
{
	struct kvm_memory_slot *slot;

	slot = kvm_vcpu_gfn_to_memslot(vcpu, gfn);
	if (!memslot_valid_for_gpte(slot, no_dirty_log))
		slot = NULL;

	return slot;
}