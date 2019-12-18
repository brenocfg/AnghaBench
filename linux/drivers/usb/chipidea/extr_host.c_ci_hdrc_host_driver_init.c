#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  hub_control; int /*<<< orphan*/  bus_suspend; } ;

/* Variables and functions */
 int /*<<< orphan*/  ci_ehci_bus_suspend ; 
 TYPE_1__ ci_ehci_hc_driver ; 
 int /*<<< orphan*/  ci_ehci_hub_control ; 
 int /*<<< orphan*/  ehci_ci_overrides ; 
 int /*<<< orphan*/  ehci_init_driver (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  orig_bus_suspend ; 

void ci_hdrc_host_driver_init(void)
{
	ehci_init_driver(&ci_ehci_hc_driver, &ehci_ci_overrides);
	orig_bus_suspend = ci_ehci_hc_driver.bus_suspend;
	ci_ehci_hc_driver.bus_suspend = ci_ehci_bus_suspend;
	ci_ehci_hc_driver.hub_control = ci_ehci_hub_control;
}