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
typedef  unsigned long long dm_block_t ;

/* Variables and functions */

__attribute__((used)) static bool valid_nr_blocks(dm_block_t n)
{
	/*
	 * dm_bitset restricts us to 2^32.  test_bit & co. restrict us
	 * further to 2^31 - 1
	 */
	return n < (1ull << 31);
}