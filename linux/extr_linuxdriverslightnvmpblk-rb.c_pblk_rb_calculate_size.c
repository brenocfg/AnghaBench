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
 int /*<<< orphan*/  get_count_order (unsigned int) ; 
 int max (int /*<<< orphan*/ ,int) ; 

unsigned int pblk_rb_calculate_size(unsigned int nr_entries)
{
	/* Alloc a write buffer that can at least fit 128 entries */
	return (1 << max(get_count_order(nr_entries), 7));
}