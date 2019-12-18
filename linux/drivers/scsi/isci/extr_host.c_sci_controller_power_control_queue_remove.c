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
struct isci_phy {size_t phy_index; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** requesters; int /*<<< orphan*/  phys_waiting; } ;
struct isci_host {TYPE_1__ power_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 

void sci_controller_power_control_queue_remove(struct isci_host *ihost,
					       struct isci_phy *iphy)
{
	BUG_ON(iphy == NULL);

	if (ihost->power_control.requesters[iphy->phy_index])
		ihost->power_control.phys_waiting--;

	ihost->power_control.requesters[iphy->phy_index] = NULL;
}