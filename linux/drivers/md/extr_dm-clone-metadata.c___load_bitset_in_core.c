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
struct dm_clone_metadata {int nr_regions; int /*<<< orphan*/  region_map; int /*<<< orphan*/  bitset_root; int /*<<< orphan*/  bitset_info; } ;
struct dm_bitset_cursor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (unsigned long,int /*<<< orphan*/ ) ; 
 int dm_bitset_cursor_begin (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct dm_bitset_cursor*) ; 
 int /*<<< orphan*/  dm_bitset_cursor_end (struct dm_bitset_cursor*) ; 
 scalar_t__ dm_bitset_cursor_get_value (struct dm_bitset_cursor*) ; 
 int dm_bitset_cursor_next (struct dm_bitset_cursor*) ; 
 int dm_bitset_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __load_bitset_in_core(struct dm_clone_metadata *cmd)
{
	int r;
	unsigned long i;
	struct dm_bitset_cursor c;

	/* Flush bitset cache */
	r = dm_bitset_flush(&cmd->bitset_info, cmd->bitset_root, &cmd->bitset_root);
	if (r)
		return r;

	r = dm_bitset_cursor_begin(&cmd->bitset_info, cmd->bitset_root, cmd->nr_regions, &c);
	if (r)
		return r;

	for (i = 0; ; i++) {
		if (dm_bitset_cursor_get_value(&c))
			__set_bit(i, cmd->region_map);
		else
			__clear_bit(i, cmd->region_map);

		if (i >= (cmd->nr_regions - 1))
			break;

		r = dm_bitset_cursor_next(&c);

		if (r)
			break;
	}

	dm_bitset_cursor_end(&c);

	return r;
}