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
typedef  int /*<<< orphan*/  u8 ;
struct isci_port {int dummy; } ;
struct isci_phy {int bcn_received_while_port_unassigned; int /*<<< orphan*/  sata_timer; int /*<<< orphan*/  max_negotiated_speed; int /*<<< orphan*/ * link_layer_registers; int /*<<< orphan*/  protocol; int /*<<< orphan*/  phy_index; struct isci_port* owning_port; int /*<<< orphan*/  sm; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_LINK_RATE_UNKNOWN ; 
 int /*<<< orphan*/  SAS_PROTOCOL_NONE ; 
 int /*<<< orphan*/  SCI_PHY_INITIAL ; 
 int /*<<< orphan*/  phy_sata_timeout ; 
 int /*<<< orphan*/  sci_init_sm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_init_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_phy_state_table ; 

void sci_phy_construct(struct isci_phy *iphy,
			    struct isci_port *iport, u8 phy_index)
{
	sci_init_sm(&iphy->sm, sci_phy_state_table, SCI_PHY_INITIAL);

	/* Copy the rest of the input data to our locals */
	iphy->owning_port = iport;
	iphy->phy_index = phy_index;
	iphy->bcn_received_while_port_unassigned = false;
	iphy->protocol = SAS_PROTOCOL_NONE;
	iphy->link_layer_registers = NULL;
	iphy->max_negotiated_speed = SAS_LINK_RATE_UNKNOWN;

	/* Create the SIGNATURE FIS Timeout timer for this phy */
	sci_init_timer(&iphy->sata_timer, phy_sata_timeout);
}