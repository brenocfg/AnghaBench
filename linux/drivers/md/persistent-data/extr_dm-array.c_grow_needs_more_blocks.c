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
struct resize {unsigned int old_nr_full_blocks; scalar_t__ old_nr_entries_in_last_block; scalar_t__ new_nr_entries_in_last_block; int /*<<< orphan*/  root; int /*<<< orphan*/  value; int /*<<< orphan*/  max_entries; int /*<<< orphan*/  new_nr_full_blocks; int /*<<< orphan*/  size_of_block; int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int grow_add_tail_block (struct resize*) ; 
 int grow_extend_tail_block (struct resize*,int /*<<< orphan*/ ) ; 
 int insert_full_ablocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int grow_needs_more_blocks(struct resize *resize)
{
	int r;
	unsigned old_nr_blocks = resize->old_nr_full_blocks;

	if (resize->old_nr_entries_in_last_block > 0) {
		old_nr_blocks++;

		r = grow_extend_tail_block(resize, resize->max_entries);
		if (r)
			return r;
	}

	r = insert_full_ablocks(resize->info, resize->size_of_block,
				old_nr_blocks,
				resize->new_nr_full_blocks,
				resize->max_entries, resize->value,
				&resize->root);
	if (r)
		return r;

	if (resize->new_nr_entries_in_last_block)
		r = grow_add_tail_block(resize);

	return r;
}