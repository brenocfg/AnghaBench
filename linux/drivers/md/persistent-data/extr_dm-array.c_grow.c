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
struct resize {scalar_t__ new_nr_full_blocks; scalar_t__ old_nr_full_blocks; int /*<<< orphan*/  new_nr_entries_in_last_block; scalar_t__ old_nr_entries_in_last_block; } ;

/* Variables and functions */
 int grow_add_tail_block (struct resize*) ; 
 int grow_extend_tail_block (struct resize*,int /*<<< orphan*/ ) ; 
 int grow_needs_more_blocks (struct resize*) ; 

__attribute__((used)) static int grow(struct resize *resize)
{
	if (resize->new_nr_full_blocks > resize->old_nr_full_blocks)
		return grow_needs_more_blocks(resize);

	else if (resize->old_nr_entries_in_last_block)
		return grow_extend_tail_block(resize, resize->new_nr_entries_in_last_block);

	else
		return grow_add_tail_block(resize);
}