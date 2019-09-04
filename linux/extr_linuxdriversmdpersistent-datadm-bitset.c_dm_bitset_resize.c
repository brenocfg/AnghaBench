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
struct dm_disk_bitset {int /*<<< orphan*/  array_info; } ;
typedef  int /*<<< orphan*/  dm_block_t ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_ARRAY_ENTRY ; 
 int /*<<< orphan*/  __dm_bless_for_disk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int dm_array_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_div_up (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int dm_bitset_resize(struct dm_disk_bitset *info, dm_block_t root,
		     uint32_t old_nr_entries, uint32_t new_nr_entries,
		     bool default_value, dm_block_t *new_root)
{
	uint32_t old_blocks = dm_div_up(old_nr_entries, BITS_PER_ARRAY_ENTRY);
	uint32_t new_blocks = dm_div_up(new_nr_entries, BITS_PER_ARRAY_ENTRY);
	__le64 value = default_value ? cpu_to_le64(~0) : cpu_to_le64(0);

	__dm_bless_for_disk(&value);
	return dm_array_resize(&info->array_info, root, old_blocks, new_blocks,
			       &value, new_root);
}