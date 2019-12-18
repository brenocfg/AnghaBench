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
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/ * valid_routes; int /*<<< orphan*/ * route_values; } ;
struct TYPE_5__ {TYPE_1__ routing_tables; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR ; 
 int /*<<< orphan*/ ** RV ; 
 TYPE_3__ board ; 
 int /*<<< orphan*/  init_private () ; 
 int /*<<< orphan*/  pci_fake ; 
 TYPE_2__ private ; 

__attribute__((used)) static void init_pci_fake(void)
{
	board.name = pci_fake;
	init_private();
	private.routing_tables.route_values = &RV[0][0];
	private.routing_tables.valid_routes = &DR;
}