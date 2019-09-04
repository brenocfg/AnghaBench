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
struct dm_bitset_cursor {int bit_index; int /*<<< orphan*/  entries_remaining; } ;

/* Variables and functions */
 int ENODATA ; 
 int cursor_next_array_entry (struct dm_bitset_cursor*) ; 

int dm_bitset_cursor_next(struct dm_bitset_cursor *c)
{
	int r = 0;

	if (!c->entries_remaining)
		return -ENODATA;

	c->entries_remaining--;
	if (++c->bit_index > 63)
		r = cursor_next_array_entry(c);

	return r;
}