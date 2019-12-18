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
 int /*<<< orphan*/  O (int) ; 
 int /*<<< orphan*/  init_pci_fake () ; 
 TYPE_1__ private ; 
 int route_register_is_valid (int,int /*<<< orphan*/ ,struct ni_route_tables const*) ; 
 int /*<<< orphan*/  unittest (int,char*) ; 

void test_route_register_is_valid(void)
{
	const struct ni_route_tables *T = &private.routing_tables;

	init_pci_fake();
	unittest(route_register_is_valid(4, O(4), T) == false,
		 "check for bad source 4-->4\n");
	unittest(route_register_is_valid(0, O(1), T) == true,
		 "find first source\n");
	unittest(route_register_is_valid(4, O(6), T) == true,
		 "find middle source\n");
	unittest(route_register_is_valid(9, O(8), T) == true,
		 "find last source");
}