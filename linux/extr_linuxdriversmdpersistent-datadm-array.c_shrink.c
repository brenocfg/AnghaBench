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
struct resize {scalar_t__ new_nr_full_blocks; scalar_t__ old_nr_full_blocks; int /*<<< orphan*/  info; int /*<<< orphan*/  new_nr_entries_in_last_block; int /*<<< orphan*/  root; int /*<<< orphan*/  old_nr_entries_in_last_block; } ;
struct dm_block {int dummy; } ;
struct array_block {int dummy; } ;

/* Variables and functions */
 int drop_blocks (struct resize*,unsigned int,unsigned int) ; 
 int shadow_ablock (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,struct dm_block**,struct array_block**) ; 
 unsigned int total_nr_blocks_needed (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trim_ablock (int /*<<< orphan*/ ,struct array_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_ablock (int /*<<< orphan*/ ,struct dm_block*) ; 

__attribute__((used)) static int shrink(struct resize *resize)
{
	int r;
	unsigned begin, end;
	struct dm_block *block;
	struct array_block *ab;

	/*
	 * Lose some blocks from the back?
	 */
	if (resize->new_nr_full_blocks < resize->old_nr_full_blocks) {
		begin = total_nr_blocks_needed(resize->new_nr_full_blocks,
					       resize->new_nr_entries_in_last_block);
		end = total_nr_blocks_needed(resize->old_nr_full_blocks,
					     resize->old_nr_entries_in_last_block);

		r = drop_blocks(resize, begin, end);
		if (r)
			return r;
	}

	/*
	 * Trim the new tail block
	 */
	if (resize->new_nr_entries_in_last_block) {
		r = shadow_ablock(resize->info, &resize->root,
				  resize->new_nr_full_blocks, &block, &ab);
		if (r)
			return r;

		trim_ablock(resize->info, ab, resize->new_nr_entries_in_last_block);
		unlock_ablock(resize->info, block);
	}

	return 0;
}