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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int phy_id; scalar_t__ force_media; } ;
struct nic {int phy; scalar_t__ mac; int flags; int* eeprom; TYPE_1__ mii; int /*<<< orphan*/  mdio_ctrl; struct net_device* netdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ADVERTISE_PAUSE_ASYM ; 
 int ADVERTISE_PAUSE_CAP ; 
 int BMCR_ISOLATE ; 
 int BMCR_RESET ; 
 int EAGAIN ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  MII_NCONFIG ; 
 int /*<<< orphan*/  MII_NSC_CONG ; 
 int /*<<< orphan*/  MII_PHYSID1 ; 
 int /*<<< orphan*/  MII_PHYSID2 ; 
 int /*<<< orphan*/  MII_TPISTATUS ; 
 int NCONFIG_AUTO_SWITCH ; 
 int NCS_PHY_MODEL_MASK ; 
 int NSC_CONG_ENABLE ; 
 int NSC_CONG_TXREADY ; 
 scalar_t__ e100_phy_check_without_mii (struct nic*) ; 
 size_t eeprom_cnfg_mdix ; 
 int eeprom_mdix_enabled ; 
 int /*<<< orphan*/  hw ; 
 int ich ; 
 scalar_t__ mac_82550_D102 ; 
 int /*<<< orphan*/  mdio_ctrl_phy_82552_v ; 
 int mdio_read (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdio_write (struct net_device*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_err (struct nic*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_printk (struct nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*,char*,int) ; 
 int phy_82552_v ; 
 int phy_nsc_tx ; 

__attribute__((used)) static int e100_phy_init(struct nic *nic)
{
	struct net_device *netdev = nic->netdev;
	u32 addr;
	u16 bmcr, stat, id_lo, id_hi, cong;

	/* Discover phy addr by searching addrs in order {1,0,2,..., 31} */
	for (addr = 0; addr < 32; addr++) {
		nic->mii.phy_id = (addr == 0) ? 1 : (addr == 1) ? 0 : addr;
		bmcr = mdio_read(netdev, nic->mii.phy_id, MII_BMCR);
		stat = mdio_read(netdev, nic->mii.phy_id, MII_BMSR);
		stat = mdio_read(netdev, nic->mii.phy_id, MII_BMSR);
		if (!((bmcr == 0xFFFF) || ((stat == 0) && (bmcr == 0))))
			break;
	}
	if (addr == 32) {
		/* uhoh, no PHY detected: check whether we seem to be some
		 * weird, rare variant which is *known* to not have any MII.
		 * But do this AFTER MII checking only, since this does
		 * lookup of EEPROM values which may easily be unreliable. */
		if (e100_phy_check_without_mii(nic))
			return 0; /* simply return and hope for the best */
		else {
			/* for unknown cases log a fatal error */
			netif_err(nic, hw, nic->netdev,
				  "Failed to locate any known PHY, aborting\n");
			return -EAGAIN;
		}
	} else
		netif_printk(nic, hw, KERN_DEBUG, nic->netdev,
			     "phy_addr = %d\n", nic->mii.phy_id);

	/* Get phy ID */
	id_lo = mdio_read(netdev, nic->mii.phy_id, MII_PHYSID1);
	id_hi = mdio_read(netdev, nic->mii.phy_id, MII_PHYSID2);
	nic->phy = (u32)id_hi << 16 | (u32)id_lo;
	netif_printk(nic, hw, KERN_DEBUG, nic->netdev,
		     "phy ID = 0x%08X\n", nic->phy);

	/* Select the phy and isolate the rest */
	for (addr = 0; addr < 32; addr++) {
		if (addr != nic->mii.phy_id) {
			mdio_write(netdev, addr, MII_BMCR, BMCR_ISOLATE);
		} else if (nic->phy != phy_82552_v) {
			bmcr = mdio_read(netdev, addr, MII_BMCR);
			mdio_write(netdev, addr, MII_BMCR,
				bmcr & ~BMCR_ISOLATE);
		}
	}
	/*
	 * Workaround for 82552:
	 * Clear the ISOLATE bit on selected phy_id last (mirrored on all
	 * other phy_id's) using bmcr value from addr discovery loop above.
	 */
	if (nic->phy == phy_82552_v)
		mdio_write(netdev, nic->mii.phy_id, MII_BMCR,
			bmcr & ~BMCR_ISOLATE);

	/* Handle National tx phys */
#define NCS_PHY_MODEL_MASK	0xFFF0FFFF
	if ((nic->phy & NCS_PHY_MODEL_MASK) == phy_nsc_tx) {
		/* Disable congestion control */
		cong = mdio_read(netdev, nic->mii.phy_id, MII_NSC_CONG);
		cong |= NSC_CONG_TXREADY;
		cong &= ~NSC_CONG_ENABLE;
		mdio_write(netdev, nic->mii.phy_id, MII_NSC_CONG, cong);
	}

	if (nic->phy == phy_82552_v) {
		u16 advert = mdio_read(netdev, nic->mii.phy_id, MII_ADVERTISE);

		/* assign special tweaked mdio_ctrl() function */
		nic->mdio_ctrl = mdio_ctrl_phy_82552_v;

		/* Workaround Si not advertising flow-control during autoneg */
		advert |= ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM;
		mdio_write(netdev, nic->mii.phy_id, MII_ADVERTISE, advert);

		/* Reset for the above changes to take effect */
		bmcr = mdio_read(netdev, nic->mii.phy_id, MII_BMCR);
		bmcr |= BMCR_RESET;
		mdio_write(netdev, nic->mii.phy_id, MII_BMCR, bmcr);
	} else if ((nic->mac >= mac_82550_D102) || ((nic->flags & ich) &&
	   (mdio_read(netdev, nic->mii.phy_id, MII_TPISTATUS) & 0x8000) &&
		(nic->eeprom[eeprom_cnfg_mdix] & eeprom_mdix_enabled))) {
		/* enable/disable MDI/MDI-X auto-switching. */
		mdio_write(netdev, nic->mii.phy_id, MII_NCONFIG,
				nic->mii.force_media ? 0 : NCONFIG_AUTO_SWITCH);
	}

	return 0;
}