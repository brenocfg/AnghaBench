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

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int validate_nr_regions(unsigned long n, char **error)
{
	/*
	 * dm_bitset restricts us to 2^32 regions. test_bit & co. restrict us
	 * further to 2^31 regions.
	 */
	if (n > (1UL << 31)) {
		*error = "Too many regions. Consider increasing the region size";
		return -EINVAL;
	}

	return 0;
}