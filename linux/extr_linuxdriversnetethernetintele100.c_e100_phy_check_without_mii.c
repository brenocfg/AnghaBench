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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  phy_id; } ;
struct nic {int* eeprom; TYPE_1__ mii; int /*<<< orphan*/  mdio_ctrl; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
#define  I82503 130 
#define  NoSuchPhy 129 
#define  S80C24 128 
 size_t eeprom_phy_iface ; 
 int /*<<< orphan*/  mdio_ctrl_phy_mii_emulated ; 
 int /*<<< orphan*/  netif_info (struct nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  probe ; 

__attribute__((used)) static int e100_phy_check_without_mii(struct nic *nic)
{
	u8 phy_type;
	int without_mii;

	phy_type = (nic->eeprom[eeprom_phy_iface] >> 8) & 0x0f;

	switch (phy_type) {
	case NoSuchPhy: /* Non-MII PHY; UNTESTED! */
	case I82503: /* Non-MII PHY; UNTESTED! */
	case S80C24: /* Non-MII PHY; tested and working */
		/* paragraph from the FreeBSD driver, "FXP_PHY_80C24":
		 * The Seeq 80c24 AutoDUPLEX(tm) Ethernet Interface Adapter
		 * doesn't have a programming interface of any sort.  The
		 * media is sensed automatically based on how the link partner
		 * is configured.  This is, in essence, manual configuration.
		 */
		netif_info(nic, probe, nic->netdev,
			   "found MII-less i82503 or 80c24 or other PHY\n");

		nic->mdio_ctrl = mdio_ctrl_phy_mii_emulated;
		nic->mii.phy_id = 0; /* is this ok for an MII-less PHY? */

		/* these might be needed for certain MII-less cards...
		 * nic->flags |= ich;
		 * nic->flags |= ich_10h_workaround; */

		without_mii = 1;
		break;
	default:
		without_mii = 0;
		break;
	}
	return without_mii;
}