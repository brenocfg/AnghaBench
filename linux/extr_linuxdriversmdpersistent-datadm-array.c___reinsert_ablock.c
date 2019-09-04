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
struct dm_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tm; } ;
struct dm_array_info {TYPE_1__ btree_info; } ;
typedef  scalar_t__ dm_block_t ;

/* Variables and functions */
 scalar_t__ dm_block_location (struct dm_block*) ; 
 int /*<<< orphan*/  dm_tm_inc (int /*<<< orphan*/ ,scalar_t__) ; 
 int insert_ablock (struct dm_array_info*,unsigned int,struct dm_block*,scalar_t__*) ; 

__attribute__((used)) static int __reinsert_ablock(struct dm_array_info *info, unsigned index,
			     struct dm_block *block, dm_block_t b,
			     dm_block_t *root)
{
	int r = 0;

	if (dm_block_location(block) != b) {
		/*
		 * dm_tm_shadow_block will have already decremented the old
		 * block, but it is still referenced by the btree.  We
		 * increment to stop the insert decrementing it below zero
		 * when overwriting the old value.
		 */
		dm_tm_inc(info->btree_info.tm, b);
		r = insert_ablock(info, index, block, root);
	}

	return r;
}