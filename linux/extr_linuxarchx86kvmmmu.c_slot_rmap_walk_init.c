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
struct slot_rmap_walk_iterator {int start_level; int end_level; void* end_gfn; void* start_gfn; struct kvm_memory_slot* slot; } ;
struct kvm_memory_slot {int dummy; } ;
typedef  void* gfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  rmap_walk_init_level (struct slot_rmap_walk_iterator*,int) ; 

__attribute__((used)) static void
slot_rmap_walk_init(struct slot_rmap_walk_iterator *iterator,
		    struct kvm_memory_slot *slot, int start_level,
		    int end_level, gfn_t start_gfn, gfn_t end_gfn)
{
	iterator->slot = slot;
	iterator->start_level = start_level;
	iterator->end_level = end_level;
	iterator->start_gfn = start_gfn;
	iterator->end_gfn = end_gfn;

	rmap_walk_init_level(iterator, iterator->start_level);
}