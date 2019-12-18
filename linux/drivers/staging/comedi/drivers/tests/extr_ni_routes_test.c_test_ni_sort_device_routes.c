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
 int /*<<< orphan*/  DR ; 
 int /*<<< orphan*/  ni_sort_device_routes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  route_set_dests_in_order (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  route_set_sources_in_order (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unittest (int /*<<< orphan*/ ,char*) ; 

void test_ni_sort_device_routes(void)
{
	/* We begin by sorting the device routes for use in later tests */
	ni_sort_device_routes(&DR);
	/* now we test that sorting. */
	unittest(route_set_dests_in_order(&DR),
		 "all route_sets of fake data in order of sig. destination\n");
	unittest(route_set_sources_in_order(&DR),
		 "all route_set->src's of fake data in order of sig. source\n");
}