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
struct pagerange_state {int not_ram; unsigned long cur_pfn; int ram; } ;

/* Variables and functions */

__attribute__((used)) static int
pagerange_is_ram_callback(unsigned long initial_pfn, unsigned long total_nr_pages, void *arg)
{
	struct pagerange_state *state = arg;

	state->not_ram	|= initial_pfn > state->cur_pfn;
	state->ram	|= total_nr_pages > 0;
	state->cur_pfn	 = initial_pfn + total_nr_pages;

	return state->ram && state->not_ram;
}