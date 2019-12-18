#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int n_route_sets; TYPE_1__* routes; } ;
struct TYPE_4__ {int /*<<< orphan*/  dest; } ;

/* Variables and functions */
 TYPE_2__ DR ; 
 int /*<<< orphan*/  bad_dest ; 
 int /*<<< orphan*/  dest0 ; 
 int /*<<< orphan*/  desti ; 
 size_t ith_dest_index ; 
 TYPE_1__* ni_find_route_set (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  no_val_dest ; 
 size_t no_val_index ; 
 int /*<<< orphan*/  unittest (int,char*) ; 

void test_ni_find_route_set(void)
{
	unittest(!ni_find_route_set(bad_dest, &DR),
		 "check for nonexistent route_set\n");
	unittest(ni_find_route_set(dest0, &DR) == &DR.routes[0],
		 "find first route_set\n");
	unittest(ni_find_route_set(desti, &DR) == &DR.routes[ith_dest_index],
		 "find ith route_set\n");
	unittest(ni_find_route_set(no_val_dest, &DR) ==
		 &DR.routes[no_val_index],
		 "find no_val route_set in spite of missing values\n");
	unittest(ni_find_route_set(DR.routes[DR.n_route_sets - 1].dest, &DR) ==
		 &DR.routes[DR.n_route_sets - 1],
		 "find last route_set\n");
}