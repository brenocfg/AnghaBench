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
struct isci_phy {int /*<<< orphan*/  protocol; int /*<<< orphan*/  sm; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_PROTOCOL_SATA ; 
 int /*<<< orphan*/  SCI_PHY_SUB_AWAIT_SATA_POWER ; 
 int /*<<< orphan*/  sci_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sci_phy_start_sata_link_training(struct isci_phy *iphy)
{
	/* This method continues the link training for the phy as if it were a SATA PHY
	 * instead of a SAS PHY.  This is done because the completion queue had a SATA
	 * SPINUP HOLD event when the state machine was expecting a SAS PHY event. none
	 */
	sci_change_state(&iphy->sm, SCI_PHY_SUB_AWAIT_SATA_POWER);

	iphy->protocol = SAS_PROTOCOL_SATA;
}