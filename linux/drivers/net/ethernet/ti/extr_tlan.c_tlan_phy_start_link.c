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
typedef  int u16 ;
struct tlan_priv {int* phy; size_t phy_num; scalar_t__ speed; scalar_t__ duplex; int tlan_full_duplex; scalar_t__ aui; } ;
struct net_device {int /*<<< orphan*/  base_addr; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  MII_AN_ADV ; 
 int MII_GC_DUPLEX ; 
 int MII_GC_SPEEDSEL ; 
 int /*<<< orphan*/  MII_GEN_CTL ; 
 int /*<<< orphan*/  MII_GEN_STS ; 
 int MII_GS_AUTONEG ; 
 int /*<<< orphan*/  TLAN_DBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLAN_DEBUG_GNRL ; 
 scalar_t__ TLAN_DUPLEX_FULL ; 
 scalar_t__ TLAN_DUPLEX_HALF ; 
 int TLAN_NET_CFG_1CHAN ; 
 int TLAN_NET_CFG_1FRAG ; 
 int TLAN_NET_CFG_PHY_EN ; 
 int /*<<< orphan*/  TLAN_NET_CONFIG ; 
 scalar_t__ TLAN_SPEED_10 ; 
 scalar_t__ TLAN_SPEED_100 ; 
 int TLAN_TC_AUISEL ; 
 int /*<<< orphan*/  TLAN_TIMER_FINISH_RESET ; 
 int /*<<< orphan*/  TLAN_TIMER_PHY_FINISH_AN ; 
 int /*<<< orphan*/  TLAN_TIMER_PHY_PDOWN ; 
 int /*<<< orphan*/  TLAN_TLPHY_CTL ; 
 int msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct tlan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  tlan_dio_write16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tlan_mii_read_reg (struct net_device*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  tlan_mii_write_reg (struct net_device*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tlan_set_timer (struct net_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tlan_phy_start_link(struct net_device *dev)
{
	struct tlan_priv	*priv = netdev_priv(dev);
	u16		ability;
	u16		control;
	u16		data;
	u16		phy;
	u16		status;
	u16		tctl;

	phy = priv->phy[priv->phy_num];
	TLAN_DBG(TLAN_DEBUG_GNRL, "%s: Trying to activate link.\n", dev->name);
	tlan_mii_read_reg(dev, phy, MII_GEN_STS, &status);
	tlan_mii_read_reg(dev, phy, MII_GEN_STS, &ability);

	if ((status & MII_GS_AUTONEG) &&
	    (!priv->aui)) {
		ability = status >> 11;
		if (priv->speed  == TLAN_SPEED_10 &&
		    priv->duplex == TLAN_DUPLEX_HALF) {
			tlan_mii_write_reg(dev, phy, MII_GEN_CTL, 0x0000);
		} else if (priv->speed == TLAN_SPEED_10 &&
			   priv->duplex == TLAN_DUPLEX_FULL) {
			priv->tlan_full_duplex = true;
			tlan_mii_write_reg(dev, phy, MII_GEN_CTL, 0x0100);
		} else if (priv->speed == TLAN_SPEED_100 &&
			   priv->duplex == TLAN_DUPLEX_HALF) {
			tlan_mii_write_reg(dev, phy, MII_GEN_CTL, 0x2000);
		} else if (priv->speed == TLAN_SPEED_100 &&
			   priv->duplex == TLAN_DUPLEX_FULL) {
			priv->tlan_full_duplex = true;
			tlan_mii_write_reg(dev, phy, MII_GEN_CTL, 0x2100);
		} else {

			/* Set Auto-Neg advertisement */
			tlan_mii_write_reg(dev, phy, MII_AN_ADV,
					   (ability << 5) | 1);
			/* Enablee Auto-Neg */
			tlan_mii_write_reg(dev, phy, MII_GEN_CTL, 0x1000);
			/* Restart Auto-Neg */
			tlan_mii_write_reg(dev, phy, MII_GEN_CTL, 0x1200);
			/* Wait for 4 sec for autonegotiation
			 * to complete.  The max spec time is less than this
			 * but the card need additional time to start AN.
			 * .5 sec should be plenty extra.
			 */
			netdev_info(dev, "Starting autonegotiation\n");
			tlan_set_timer(dev, (2*HZ), TLAN_TIMER_PHY_FINISH_AN);
			return;
		}

	}

	if ((priv->aui) && (priv->phy_num != 0)) {
		priv->phy_num = 0;
		data = TLAN_NET_CFG_1FRAG | TLAN_NET_CFG_1CHAN
			| TLAN_NET_CFG_PHY_EN;
		tlan_dio_write16(dev->base_addr, TLAN_NET_CONFIG, data);
		tlan_set_timer(dev, msecs_to_jiffies(40), TLAN_TIMER_PHY_PDOWN);
		return;
	} else if (priv->phy_num == 0) {
		control = 0;
		tlan_mii_read_reg(dev, phy, TLAN_TLPHY_CTL, &tctl);
		if (priv->aui) {
			tctl |= TLAN_TC_AUISEL;
		} else {
			tctl &= ~TLAN_TC_AUISEL;
			if (priv->duplex == TLAN_DUPLEX_FULL) {
				control |= MII_GC_DUPLEX;
				priv->tlan_full_duplex = true;
			}
			if (priv->speed == TLAN_SPEED_100)
				control |= MII_GC_SPEEDSEL;
		}
		tlan_mii_write_reg(dev, phy, MII_GEN_CTL, control);
		tlan_mii_write_reg(dev, phy, TLAN_TLPHY_CTL, tctl);
	}

	/* Wait for 2 sec to give the transceiver time
	 * to establish link.
	 */
	tlan_set_timer(dev, (4*HZ), TLAN_TIMER_FINISH_RESET);

}