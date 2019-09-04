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
struct slot_rmap_walk_iterator {scalar_t__ rmap; scalar_t__ end_rmap; unsigned long gfn; scalar_t__ level; scalar_t__ end_level; } ;

/* Variables and functions */
 unsigned long KVM_HPAGE_GFN_SHIFT (scalar_t__) ; 
 int /*<<< orphan*/  rmap_walk_init_level (struct slot_rmap_walk_iterator*,scalar_t__) ; 

__attribute__((used)) static void slot_rmap_walk_next(struct slot_rmap_walk_iterator *iterator)
{
	if (++iterator->rmap <= iterator->end_rmap) {
		iterator->gfn += (1UL << KVM_HPAGE_GFN_SHIFT(iterator->level));
		return;
	}

	if (++iterator->level > iterator->end_level) {
		iterator->rmap = NULL;
		return;
	}

	rmap_walk_init_level(iterator, iterator->level);
}