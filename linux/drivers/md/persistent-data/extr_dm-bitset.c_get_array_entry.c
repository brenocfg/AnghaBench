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
typedef  unsigned int uint32_t ;
struct dm_disk_bitset {unsigned int current_index; scalar_t__ current_index_set; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 unsigned int BITS_PER_ARRAY_ENTRY ; 
 int dm_bitset_flush (struct dm_disk_bitset*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int read_bits (struct dm_disk_bitset*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int get_array_entry(struct dm_disk_bitset *info, dm_block_t root,
			   uint32_t index, dm_block_t *new_root)
{
	int r;
	unsigned array_index = index / BITS_PER_ARRAY_ENTRY;

	if (info->current_index_set) {
		if (info->current_index == array_index)
			return 0;

		r = dm_bitset_flush(info, root, new_root);
		if (r)
			return r;
	}

	return read_bits(info, root, array_index);
}