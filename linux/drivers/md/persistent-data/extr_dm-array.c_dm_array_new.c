#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  value_fn ;
typedef  unsigned int uint32_t ;
struct dm_block {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; } ;
struct TYPE_3__ {int /*<<< orphan*/  tm; } ;
struct dm_array_info {TYPE_2__ value_type; TYPE_1__ btree_info; } ;
struct array_block {int dummy; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int alloc_ablock (struct dm_array_info*,unsigned int,unsigned int,struct dm_block**,struct array_block**) ; 
 unsigned int calc_max_entries (int /*<<< orphan*/ ,unsigned int) ; 
 int dm_array_empty (struct dm_array_info*,int /*<<< orphan*/ *) ; 
 unsigned int dm_bm_block_size (int /*<<< orphan*/ ) ; 
 unsigned int dm_div_up (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dm_tm_get_bm (int /*<<< orphan*/ ) ; 
 int insert_ablock (struct dm_array_info*,unsigned int,struct dm_block*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  min (unsigned int,unsigned int) ; 
 int populate_ablock_with_values (struct dm_array_info*,struct array_block*,int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_ablock (struct dm_array_info*,struct dm_block*) ; 

int dm_array_new(struct dm_array_info *info, dm_block_t *root,
		 uint32_t size, value_fn fn, void *context)
{
	int r;
	struct dm_block *block;
	struct array_block *ab;
	unsigned block_index, end_block, size_of_block, max_entries;

	r = dm_array_empty(info, root);
	if (r)
		return r;

	size_of_block = dm_bm_block_size(dm_tm_get_bm(info->btree_info.tm));
	max_entries = calc_max_entries(info->value_type.size, size_of_block);
	end_block = dm_div_up(size, max_entries);

	for (block_index = 0; block_index != end_block; block_index++) {
		r = alloc_ablock(info, size_of_block, max_entries, &block, &ab);
		if (r)
			break;

		r = populate_ablock_with_values(info, ab, fn, context,
						block_index * max_entries,
						min(max_entries, size));
		if (r) {
			unlock_ablock(info, block);
			break;
		}

		r = insert_ablock(info, block_index, block, root);
		unlock_ablock(info, block);
		if (r)
			break;

		size -= max_entries;
	}

	return r;
}