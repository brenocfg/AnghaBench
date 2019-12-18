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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  phy_id; } ;
struct jme_adapter {int phylink; int reg_ghc; int reg_gpreg1; int /*<<< orphan*/  dev; int /*<<< orphan*/  chiprev; TYPE_2__* pdev; scalar_t__ fpgaver; TYPE_1__ mii_if; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int BMCR_FULLDPLX ; 
 int BMCR_SPEED100 ; 
 int BMCR_SPEED1000 ; 
 int GHC_DPX ; 
 int GHC_SPEED_1000M ; 
 int GHC_SPEED_100M ; 
 int GHC_SPEED_10M ; 
 int GPREG1_HALFMODEPATCH ; 
 int GPREG1_RSSPATCH ; 
 int /*<<< orphan*/  JME_GHC ; 
 int /*<<< orphan*/  JME_GPREG1 ; 
 int /*<<< orphan*/  JME_PHY_LINK ; 
 int JME_SPDRSV_TIMEOUT ; 
 int /*<<< orphan*/  JME_TXMCS ; 
 int /*<<< orphan*/  JME_TXTRHD ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int PHY_LINK_AUTONEG_COMPLETE ; 
 int PHY_LINK_DUPLEX ; 
 int PHY_LINK_MDI_STAT ; 
 int PHY_LINK_SPEEDDPU_RESOLVED ; 
#define  PHY_LINK_SPEED_1000M 130 
#define  PHY_LINK_SPEED_100M 129 
#define  PHY_LINK_SPEED_10M 128 
 int PHY_LINK_SPEED_MASK ; 
 int PHY_LINK_UP ; 
 int TXMCS_BACKOFF ; 
 int TXMCS_CARRIERSENSE ; 
 int TXMCS_COLLISION ; 
 int TXMCS_DEFAULT ; 
 int TXTRHD_FULLDUPLEX ; 
 int TXTRHD_HALFDUPLEX ; 
 scalar_t__ is_buggy250 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int jme_linkstat_from_phy (struct jme_adapter*) ; 
 int jme_mdio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jme_set_phyfifo_5level (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_set_phyfifo_8level (struct jme_adapter*) ; 
 int jread32 (struct jme_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jwrite32 (struct jme_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  link ; 
 struct jme_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct jme_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
jme_check_link(struct net_device *netdev, int testonly)
{
	struct jme_adapter *jme = netdev_priv(netdev);
	u32 phylink, cnt = JME_SPDRSV_TIMEOUT, bmcr;
	char linkmsg[64];
	int rc = 0;

	linkmsg[0] = '\0';

	if (jme->fpgaver)
		phylink = jme_linkstat_from_phy(jme);
	else
		phylink = jread32(jme, JME_PHY_LINK);

	if (phylink & PHY_LINK_UP) {
		if (!(phylink & PHY_LINK_AUTONEG_COMPLETE)) {
			/*
			 * If we did not enable AN
			 * Speed/Duplex Info should be obtained from SMI
			 */
			phylink = PHY_LINK_UP;

			bmcr = jme_mdio_read(jme->dev,
						jme->mii_if.phy_id,
						MII_BMCR);

			phylink |= ((bmcr & BMCR_SPEED1000) &&
					(bmcr & BMCR_SPEED100) == 0) ?
					PHY_LINK_SPEED_1000M :
					(bmcr & BMCR_SPEED100) ?
					PHY_LINK_SPEED_100M :
					PHY_LINK_SPEED_10M;

			phylink |= (bmcr & BMCR_FULLDPLX) ?
					 PHY_LINK_DUPLEX : 0;

			strcat(linkmsg, "Forced: ");
		} else {
			/*
			 * Keep polling for speed/duplex resolve complete
			 */
			while (!(phylink & PHY_LINK_SPEEDDPU_RESOLVED) &&
				--cnt) {

				udelay(1);

				if (jme->fpgaver)
					phylink = jme_linkstat_from_phy(jme);
				else
					phylink = jread32(jme, JME_PHY_LINK);
			}
			if (!cnt)
				pr_err("Waiting speed resolve timeout\n");

			strcat(linkmsg, "ANed: ");
		}

		if (jme->phylink == phylink) {
			rc = 1;
			goto out;
		}
		if (testonly)
			goto out;

		jme->phylink = phylink;

		/*
		 * The speed/duplex setting of jme->reg_ghc already cleared
		 * by jme_reset_mac_processor()
		 */
		switch (phylink & PHY_LINK_SPEED_MASK) {
		case PHY_LINK_SPEED_10M:
			jme->reg_ghc |= GHC_SPEED_10M;
			strcat(linkmsg, "10 Mbps, ");
			break;
		case PHY_LINK_SPEED_100M:
			jme->reg_ghc |= GHC_SPEED_100M;
			strcat(linkmsg, "100 Mbps, ");
			break;
		case PHY_LINK_SPEED_1000M:
			jme->reg_ghc |= GHC_SPEED_1000M;
			strcat(linkmsg, "1000 Mbps, ");
			break;
		default:
			break;
		}

		if (phylink & PHY_LINK_DUPLEX) {
			jwrite32(jme, JME_TXMCS, TXMCS_DEFAULT);
			jwrite32(jme, JME_TXTRHD, TXTRHD_FULLDUPLEX);
			jme->reg_ghc |= GHC_DPX;
		} else {
			jwrite32(jme, JME_TXMCS, TXMCS_DEFAULT |
						TXMCS_BACKOFF |
						TXMCS_CARRIERSENSE |
						TXMCS_COLLISION);
			jwrite32(jme, JME_TXTRHD, TXTRHD_HALFDUPLEX);
		}

		jwrite32(jme, JME_GHC, jme->reg_ghc);

		if (is_buggy250(jme->pdev->device, jme->chiprev)) {
			jme->reg_gpreg1 &= ~(GPREG1_HALFMODEPATCH |
					     GPREG1_RSSPATCH);
			if (!(phylink & PHY_LINK_DUPLEX))
				jme->reg_gpreg1 |= GPREG1_HALFMODEPATCH;
			switch (phylink & PHY_LINK_SPEED_MASK) {
			case PHY_LINK_SPEED_10M:
				jme_set_phyfifo_8level(jme);
				jme->reg_gpreg1 |= GPREG1_RSSPATCH;
				break;
			case PHY_LINK_SPEED_100M:
				jme_set_phyfifo_5level(jme);
				jme->reg_gpreg1 |= GPREG1_RSSPATCH;
				break;
			case PHY_LINK_SPEED_1000M:
				jme_set_phyfifo_8level(jme);
				break;
			default:
				break;
			}
		}
		jwrite32(jme, JME_GPREG1, jme->reg_gpreg1);

		strcat(linkmsg, (phylink & PHY_LINK_DUPLEX) ?
					"Full-Duplex, " :
					"Half-Duplex, ");
		strcat(linkmsg, (phylink & PHY_LINK_MDI_STAT) ?
					"MDI-X" :
					"MDI");
		netif_info(jme, link, jme->dev, "Link is up at %s\n", linkmsg);
		netif_carrier_on(netdev);
	} else {
		if (testonly)
			goto out;

		netif_info(jme, link, jme->dev, "Link is down\n");
		jme->phylink = 0;
		netif_carrier_off(netdev);
	}

out:
	return rc;
}