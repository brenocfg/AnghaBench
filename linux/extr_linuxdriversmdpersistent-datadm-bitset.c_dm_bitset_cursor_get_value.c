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
struct dm_bitset_cursor {int /*<<< orphan*/  current_bits; int /*<<< orphan*/  bit_index; } ;

/* Variables and functions */
 int test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

bool dm_bitset_cursor_get_value(struct dm_bitset_cursor *c)
{
	return test_bit(c->bit_index, (unsigned long *) &c->current_bits);
}