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
struct ni_route_tables {int dummy; } ;
struct TYPE_2__ {struct ni_route_tables routing_tables; } ;

/* Variables and functions */
 unsigned int O (int) ; 
 int /*<<< orphan*/  init_pci_fake () ; 
 int ni_get_valid_routes (struct ni_route_tables const*,int,unsigned int*) ; 
 TYPE_1__ private ; 
 int /*<<< orphan*/  unittest (int,char*) ; 

void test_ni_get_valid_routes(void)
{
	const struct ni_route_tables *T = &private.routing_tables;
	unsigned int pair_data[2];

	init_pci_fake();
	unittest(ni_get_valid_routes(T, 0, NULL) == 57,
		 "count all valid routes through ni_get_valid_routes\n");

	unittest(ni_get_valid_routes(T, 1, pair_data) == 1,
		 "copied first valid route from ni_get_valid_routes\n");
	unittest(pair_data[0] == O(1),
		 "source of first valid pair from ni_get_valid_routes\n");
	unittest(pair_data[1] == O(0),
		 "destination of first valid pair from ni_get_valid_routes\n");
}