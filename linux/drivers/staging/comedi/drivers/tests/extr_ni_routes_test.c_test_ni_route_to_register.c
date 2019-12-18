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
 int BIT (int) ; 
 int /*<<< orphan*/  O (int) ; 
 int /*<<< orphan*/  TRIGGER_LINE (int) ; 
 int /*<<< orphan*/  brd0_src0 ; 
 int /*<<< orphan*/  brd0_src1 ; 
 int /*<<< orphan*/  brd1_src0 ; 
 int /*<<< orphan*/  brd1_src1 ; 
 int /*<<< orphan*/  brd2_src0 ; 
 int /*<<< orphan*/  brd2_src1 ; 
 int /*<<< orphan*/  brd3_src0 ; 
 int /*<<< orphan*/  brd3_src1 ; 
 int /*<<< orphan*/  init_pci_fake () ; 
 int ni_route_to_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ni_route_tables const*) ; 
 TYPE_1__ private ; 
 int /*<<< orphan*/  rgout0_src0 ; 
 int /*<<< orphan*/  rgout0_src1 ; 
 int /*<<< orphan*/  unittest (int,char*) ; 

void test_ni_route_to_register(void)
{
	const struct ni_route_tables *T = &private.routing_tables;

	init_pci_fake();
	unittest(ni_route_to_register(O(0), O(0), T) < 0,
		 "check for bad route 0-->0\n");
	unittest(ni_route_to_register(O(1), O(0), T) == 1,
		 "validate first destination\n");
	unittest(ni_route_to_register(O(6), O(5), T) == 6,
		 "validate middle destination\n");
	unittest(ni_route_to_register(O(8), O(9), T) == 8,
		 "validate last destination\n");

	/* choice of trigger line in the following is somewhat random */
	unittest(ni_route_to_register(rgout0_src0, TRIGGER_LINE(0), T) == 0,
		 "validate indirect route through rgout0 to TRIGGER_LINE(0)\n");
	unittest(ni_route_to_register(rgout0_src0, TRIGGER_LINE(1), T) == 0,
		 "validate indirect route through rgout0 to TRIGGER_LINE(1)\n");
	unittest(ni_route_to_register(rgout0_src1, TRIGGER_LINE(2), T) == 1,
		 "validate indirect route through rgout0 to TRIGGER_LINE(2)\n");
	unittest(ni_route_to_register(rgout0_src1, TRIGGER_LINE(3), T) == 1,
		 "validate indirect route through rgout0 to TRIGGER_LINE(3)\n");

	unittest(ni_route_to_register(brd0_src0, TRIGGER_LINE(4), T) ==
		 BIT(6),
		 "validate indirect route through brd0 to TRIGGER_LINE(4)\n");
	unittest(ni_route_to_register(brd0_src1, TRIGGER_LINE(4), T) ==
		 BIT(6),
		 "validate indirect route through brd0 to TRIGGER_LINE(4)\n");
	unittest(ni_route_to_register(brd1_src0, TRIGGER_LINE(3), T) ==
		 BIT(6),
		 "validate indirect route through brd1 to TRIGGER_LINE(3)\n");
	unittest(ni_route_to_register(brd1_src1, TRIGGER_LINE(3), T) ==
		 BIT(6),
		 "validate indirect route through brd1 to TRIGGER_LINE(3)\n");
	unittest(ni_route_to_register(brd2_src0, TRIGGER_LINE(2), T) ==
		 BIT(6),
		 "validate indirect route through brd2 to TRIGGER_LINE(2)\n");
	unittest(ni_route_to_register(brd2_src1, TRIGGER_LINE(2), T) ==
		 BIT(6),
		 "validate indirect route through brd2 to TRIGGER_LINE(2)\n");
	unittest(ni_route_to_register(brd3_src0, TRIGGER_LINE(1), T) ==
		 BIT(6),
		 "validate indirect route through brd3 to TRIGGER_LINE(1)\n");
	unittest(ni_route_to_register(brd3_src1, TRIGGER_LINE(1), T) ==
		 BIT(6),
		 "validate indirect route through brd3 to TRIGGER_LINE(1)\n");
}