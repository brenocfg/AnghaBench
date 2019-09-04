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
struct TYPE_2__ {int /*<<< orphan*/ ** lpage_info; int /*<<< orphan*/ ** rmap; } ;
struct kvm_memory_slot {TYPE_1__ arch; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int KVM_NR_PAGE_SIZES ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_page_track_free_memslot (struct kvm_memory_slot*,struct kvm_memory_slot*) ; 

void kvm_arch_free_memslot(struct kvm *kvm, struct kvm_memory_slot *free,
			   struct kvm_memory_slot *dont)
{
	int i;

	for (i = 0; i < KVM_NR_PAGE_SIZES; ++i) {
		if (!dont || free->arch.rmap[i] != dont->arch.rmap[i]) {
			kvfree(free->arch.rmap[i]);
			free->arch.rmap[i] = NULL;
		}
		if (i == 0)
			continue;

		if (!dont || free->arch.lpage_info[i - 1] !=
			     dont->arch.lpage_info[i - 1]) {
			kvfree(free->arch.lpage_info[i - 1]);
			free->arch.lpage_info[i - 1] = NULL;
		}
	}

	kvm_page_track_free_memslot(free, dont);
}