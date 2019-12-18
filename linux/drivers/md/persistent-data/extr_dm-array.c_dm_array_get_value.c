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
typedef  unsigned int uint32_t ;
struct dm_block {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; } ;
struct TYPE_4__ {int /*<<< orphan*/  tm; } ;
struct dm_array_info {TYPE_1__ value_type; TYPE_2__ btree_info; } ;
struct array_block {int /*<<< orphan*/  nr_entries; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int ENODATA ; 
 unsigned int calc_max_entries (int /*<<< orphan*/ ,size_t) ; 
 size_t dm_bm_block_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_tm_get_bm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  element_at (struct dm_array_info*,struct array_block*,unsigned int) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int lookup_ablock (struct dm_array_info*,int /*<<< orphan*/ ,unsigned int,struct dm_block**,struct array_block**) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_ablock (struct dm_array_info*,struct dm_block*) ; 

int dm_array_get_value(struct dm_array_info *info, dm_block_t root,
		       uint32_t index, void *value_le)
{
	int r;
	struct dm_block *block;
	struct array_block *ab;
	size_t size_of_block;
	unsigned entry, max_entries;

	size_of_block = dm_bm_block_size(dm_tm_get_bm(info->btree_info.tm));
	max_entries = calc_max_entries(info->value_type.size, size_of_block);

	r = lookup_ablock(info, root, index / max_entries, &block, &ab);
	if (r)
		return r;

	entry = index % max_entries;
	if (entry >= le32_to_cpu(ab->nr_entries))
		r = -ENODATA;
	else
		memcpy(value_le, element_at(info, ab, entry),
		       info->value_type.size);

	unlock_ablock(info, block);
	return r;
}