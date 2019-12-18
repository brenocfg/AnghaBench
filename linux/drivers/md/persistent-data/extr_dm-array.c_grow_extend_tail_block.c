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
typedef  int /*<<< orphan*/  uint32_t ;
struct resize {int /*<<< orphan*/  info; int /*<<< orphan*/  value; int /*<<< orphan*/  old_nr_full_blocks; int /*<<< orphan*/  root; } ;
struct dm_block {int dummy; } ;
struct array_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fill_ablock (int /*<<< orphan*/ ,struct array_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int shadow_ablock (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dm_block**,struct array_block**) ; 
 int /*<<< orphan*/  unlock_ablock (int /*<<< orphan*/ ,struct dm_block*) ; 

__attribute__((used)) static int grow_extend_tail_block(struct resize *resize, uint32_t new_nr_entries)
{
	int r;
	struct dm_block *block;
	struct array_block *ab;

	r = shadow_ablock(resize->info, &resize->root,
			  resize->old_nr_full_blocks, &block, &ab);
	if (r)
		return r;

	fill_ablock(resize->info, ab, resize->value, new_nr_entries);
	unlock_ablock(resize->info, block);

	return r;
}