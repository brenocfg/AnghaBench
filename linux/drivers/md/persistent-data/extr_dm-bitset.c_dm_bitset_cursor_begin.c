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
typedef  scalar_t__ uint32_t ;
struct dm_disk_bitset {int /*<<< orphan*/  array_info; } ;
struct dm_bitset_cursor {int /*<<< orphan*/  current_bits; scalar_t__ bit_index; scalar_t__ array_index; int /*<<< orphan*/  cursor; scalar_t__ entries_remaining; struct dm_disk_bitset* info; } ;
typedef  int /*<<< orphan*/  dm_block_t ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int ENODATA ; 
 int dm_array_cursor_begin (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_array_cursor_get_value (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 

int dm_bitset_cursor_begin(struct dm_disk_bitset *info,
			   dm_block_t root, uint32_t nr_entries,
			   struct dm_bitset_cursor *c)
{
	int r;
	__le64 *value;

	if (!nr_entries)
		return -ENODATA;

	c->info = info;
	c->entries_remaining = nr_entries;

	r = dm_array_cursor_begin(&info->array_info, root, &c->cursor);
	if (r)
		return r;

	dm_array_cursor_get_value(&c->cursor, (void **) &value);
	c->array_index = 0;
	c->bit_index = 0;
	c->current_bits = le64_to_cpu(*value);

	return r;
}