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

__attribute__((used)) static unsigned total_nr_blocks_needed(unsigned nr_full_blocks,
				       unsigned nr_entries_in_last_block)
{
	return nr_full_blocks + (nr_entries_in_last_block ? 1 : 0);
}