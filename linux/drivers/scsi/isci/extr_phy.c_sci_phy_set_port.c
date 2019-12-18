#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct isci_port {int dummy; } ;
struct isci_phy {int bcn_received_while_port_unassigned; struct isci_port* owning_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  sci_port_broadcast_change_received (struct isci_port*,struct isci_phy*) ; 

void sci_phy_set_port(
	struct isci_phy *iphy,
	struct isci_port *iport)
{
	iphy->owning_port = iport;

	if (iphy->bcn_received_while_port_unassigned) {
		iphy->bcn_received_while_port_unassigned = false;
		sci_port_broadcast_change_received(iphy->owning_port, iphy);
	}
}