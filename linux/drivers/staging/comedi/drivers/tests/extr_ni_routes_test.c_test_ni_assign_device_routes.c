#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ni_device_routes {int n_route_sets; int /*<<< orphan*/  device; TYPE_1__* routes; } ;
struct TYPE_6__ {int /*<<< orphan*/ * route_values; struct ni_device_routes* valid_routes; } ;
struct TYPE_5__ {TYPE_3__ routing_tables; } ;
struct TYPE_4__ {scalar_t__ dest; int n_src; scalar_t__* src; } ;

/* Variables and functions */
 int /*<<< orphan*/  B (scalar_t__) ; 
 scalar_t__ NI_10MHzRefClock ; 
 scalar_t__ NI_AI_ConvertClock ; 
 scalar_t__ NI_AI_SampleClock ; 
 scalar_t__ NI_AI_StartTrigger ; 
 scalar_t__ NI_CtrSource (int /*<<< orphan*/ ) ; 
 scalar_t__ NI_PFI (int) ; 
 int NI_PFI_OUTPUT_AI_CONVERT ; 
 scalar_t__ PXI_Star ; 
 scalar_t__ RVi (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRIGGER_LINE (int /*<<< orphan*/ ) ; 
 scalar_t__ V (int) ; 
 int /*<<< orphan*/  init_pci_6070e () ; 
 int /*<<< orphan*/  init_pci_6220 () ; 
 int /*<<< orphan*/  ni_assign_device_routes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ni_eseries ; 
 int /*<<< orphan*/  ni_mseries ; 
 int /*<<< orphan*/  pci_6070e ; 
 int /*<<< orphan*/  pci_6220 ; 
 TYPE_2__ private ; 
 int route_set_dests_in_order (struct ni_device_routes const*) ; 
 int route_set_sources_in_order (struct ni_device_routes const*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unittest (int,char*) ; 

void test_ni_assign_device_routes(void)
{
	const struct ni_device_routes *devroutes, *olddevroutes;
	const u8 *table, *oldtable;

	init_pci_6070e();
	ni_assign_device_routes(ni_eseries, pci_6070e, &private.routing_tables);
	devroutes = private.routing_tables.valid_routes;
	table = private.routing_tables.route_values;

	unittest(strncmp(devroutes->device, pci_6070e, 10) == 0,
		 "find device pci-6070e\n");
	unittest(devroutes->n_route_sets == 37,
		 "number of pci-6070e route_sets == 37\n");
	unittest(devroutes->routes->dest == NI_PFI(0),
		 "first pci-6070e route_set is for NI_PFI(0)\n");
	unittest(devroutes->routes->n_src == 1,
		 "first pci-6070e route_set length == 1\n");
	unittest(devroutes->routes->src[0] == NI_AI_StartTrigger,
		 "first pci-6070e route_set src. == NI_AI_StartTrigger\n");
	unittest(devroutes->routes[10].dest == TRIGGER_LINE(0),
		 "10th pci-6070e route_set is for TRIGGER_LINE(0)\n");
	unittest(devroutes->routes[10].n_src == 10,
		 "10th pci-6070e route_set length == 10\n");
	unittest(devroutes->routes[10].src[0] == NI_CtrSource(0),
		 "10th pci-6070e route_set src. == NI_CtrSource(0)\n");
	unittest(route_set_dests_in_order(devroutes),
		 "all pci-6070e route_sets in order of signal destination\n");
	unittest(route_set_sources_in_order(devroutes),
		 "all pci-6070e route_set->src's in order of signal source\n");

	unittest(
	  RVi(table, B(PXI_Star), B(NI_AI_SampleClock)) == V(17) &&
	  RVi(table, B(NI_10MHzRefClock), B(TRIGGER_LINE(0))) == 0 &&
	  RVi(table, B(NI_AI_ConvertClock), B(NI_PFI(0))) == 0 &&
	  RVi(table, B(NI_AI_ConvertClock), B(NI_PFI(2))) ==
		V(NI_PFI_OUTPUT_AI_CONVERT),
	  "pci-6070e finds e-series route_values table\n");

	olddevroutes = devroutes;
	oldtable = table;
	init_pci_6220();
	ni_assign_device_routes(ni_mseries, pci_6220, &private.routing_tables);
	devroutes = private.routing_tables.valid_routes;
	table = private.routing_tables.route_values;

	unittest(strncmp(devroutes->device, pci_6220, 10) == 0,
		 "find device pci-6220\n");
	unittest(oldtable != table, "pci-6220 find other route_values table\n");

	unittest(
	  RVi(table, B(PXI_Star), B(NI_AI_SampleClock)) == V(20) &&
	  RVi(table, B(NI_10MHzRefClock), B(TRIGGER_LINE(0))) == V(12) &&
	  RVi(table, B(NI_AI_ConvertClock), B(NI_PFI(0))) == V(3) &&
	  RVi(table, B(NI_AI_ConvertClock), B(NI_PFI(2))) == V(3),
	  "pci-6220 finds m-series route_values table\n");
}