#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * routes; } ;

/* Variables and functions */
 TYPE_1__ DR ; 
 int /*<<< orphan*/  O (int) ; 
 int ni_route_set_has_source (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unittest (int,char*) ; 

void test_ni_route_set_has_source(void)
{
	unittest(!ni_route_set_has_source(&DR.routes[0], O(0)),
		 "check for bad source\n");
	unittest(ni_route_set_has_source(&DR.routes[0], O(1)),
		 "find first source\n");
	unittest(ni_route_set_has_source(&DR.routes[0], O(5)),
		 "find fifth source\n");
	unittest(ni_route_set_has_source(&DR.routes[0], O(9)),
		 "find last source\n");
}