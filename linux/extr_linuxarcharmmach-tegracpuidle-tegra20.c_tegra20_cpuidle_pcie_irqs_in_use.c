#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* states; } ;
struct TYPE_3__ {int disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info_once (char*) ; 
 TYPE_2__ tegra_idle_driver ; 

void tegra20_cpuidle_pcie_irqs_in_use(void)
{
	pr_info_once(
		"Disabling cpuidle LP2 state, since PCIe IRQs are in use\n");
	tegra_idle_driver.states[1].disabled = true;
}