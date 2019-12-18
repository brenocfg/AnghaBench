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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_4__ {scalar_t__ expires; } ;
struct tlan_priv {size_t phy_num; int phy_online; int rx_list_dma; TYPE_2__ media_timer; scalar_t__ aui; TYPE_1__* adapter; scalar_t__ tlan_full_duplex; int /*<<< orphan*/ * phy; } ;
struct net_device {scalar_t__ base_addr; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  MII_AN_LPA ; 
 int /*<<< orphan*/  MII_GEN_ID_HI ; 
 int /*<<< orphan*/  MII_GEN_ID_LO ; 
 int /*<<< orphan*/  MII_GEN_STS ; 
 int MII_GS_LINK ; 
 int NAT_SEM_ID1 ; 
 int NAT_SEM_ID2 ; 
 int TLAN_ADAPTER_UNMANAGED_PHY ; 
 scalar_t__ TLAN_CH_PARM ; 
 int TLAN_DEBUG_PROBE ; 
 int TLAN_HC_GO ; 
 int TLAN_HC_INT_ON ; 
 int TLAN_HC_REQ_INT ; 
 int TLAN_HC_RT ; 
 scalar_t__ TLAN_HOST_CMD ; 
 int TLAN_LED_LINK ; 
 int /*<<< orphan*/  TLAN_LED_REG ; 
 int /*<<< orphan*/  TLAN_MAX_RX ; 
 int /*<<< orphan*/  TLAN_NET_CMD ; 
 int TLAN_NET_CMD_DUPLEX ; 
 int TLAN_NET_CMD_NRESET ; 
 int TLAN_NET_CMD_NWRAP ; 
 int /*<<< orphan*/  TLAN_NET_MASK ; 
 int TLAN_NET_MASK_MASK4 ; 
 int TLAN_NET_MASK_MASK5 ; 
 int TLAN_NET_MASK_MASK7 ; 
 int /*<<< orphan*/  TLAN_NET_SIO ; 
 int TLAN_NET_SIO_MINTEN ; 
 int TLAN_PHY_AN_EN_STAT ; 
 int TLAN_PHY_DUPLEX_FULL ; 
 int TLAN_PHY_SPEED_100 ; 
 int TLAN_TC_INTEN ; 
 int /*<<< orphan*/  TLAN_TIMER_FINISH_RESET ; 
 int /*<<< orphan*/  TLAN_TLPHY_CTL ; 
 int /*<<< orphan*/  TLAN_TLPHY_PAR ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int debug ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/ * media ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,...) ; 
 struct tlan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int tlan_dio_read8 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlan_dio_write16 (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tlan_dio_write8 (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tlan_mii_read_reg (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  tlan_mii_write_reg (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tlan_set_mac (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlan_set_multicast_list (struct net_device*) ; 
 int /*<<< orphan*/  tlan_set_timer (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
tlan_finish_reset(struct net_device *dev)
{
	struct tlan_priv	*priv = netdev_priv(dev);
	u8		data;
	u32		phy;
	u8		sio;
	u16		status;
	u16		partner;
	u16		tlphy_ctl;
	u16		tlphy_par;
	u16		tlphy_id1, tlphy_id2;
	int		i;

	phy = priv->phy[priv->phy_num];

	data = TLAN_NET_CMD_NRESET | TLAN_NET_CMD_NWRAP;
	if (priv->tlan_full_duplex)
		data |= TLAN_NET_CMD_DUPLEX;
	tlan_dio_write8(dev->base_addr, TLAN_NET_CMD, data);
	data = TLAN_NET_MASK_MASK4 | TLAN_NET_MASK_MASK5;
	if (priv->phy_num == 0)
		data |= TLAN_NET_MASK_MASK7;
	tlan_dio_write8(dev->base_addr, TLAN_NET_MASK, data);
	tlan_dio_write16(dev->base_addr, TLAN_MAX_RX, ((1536)+7)&~7);
	tlan_mii_read_reg(dev, phy, MII_GEN_ID_HI, &tlphy_id1);
	tlan_mii_read_reg(dev, phy, MII_GEN_ID_LO, &tlphy_id2);

	if ((priv->adapter->flags & TLAN_ADAPTER_UNMANAGED_PHY) ||
	    (priv->aui)) {
		status = MII_GS_LINK;
		netdev_info(dev, "Link forced\n");
	} else {
		tlan_mii_read_reg(dev, phy, MII_GEN_STS, &status);
		udelay(1000);
		tlan_mii_read_reg(dev, phy, MII_GEN_STS, &status);
		if (status & MII_GS_LINK) {
			/* We only support link info on Nat.Sem. PHY's */
			if ((tlphy_id1 == NAT_SEM_ID1) &&
			    (tlphy_id2 == NAT_SEM_ID2)) {
				tlan_mii_read_reg(dev, phy, MII_AN_LPA,
					&partner);
				tlan_mii_read_reg(dev, phy, TLAN_TLPHY_PAR,
					&tlphy_par);

				netdev_info(dev,
					"Link active, %s %uMbps %s-Duplex\n",
					!(tlphy_par & TLAN_PHY_AN_EN_STAT)
					? "forced" : "Autonegotiation enabled,",
					tlphy_par & TLAN_PHY_SPEED_100
					? 100 : 10,
					tlphy_par & TLAN_PHY_DUPLEX_FULL
					? "Full" : "Half");

				if (tlphy_par & TLAN_PHY_AN_EN_STAT) {
					netdev_info(dev, "Partner capability:");
					for (i = 5; i < 10; i++)
						if (partner & (1 << i))
							pr_cont(" %s",
								media[i-5]);
					pr_cont("\n");
				}
			} else
				netdev_info(dev, "Link active\n");
			/* Enabling link beat monitoring */
			priv->media_timer.expires = jiffies + HZ;
			add_timer(&priv->media_timer);
		}
	}

	if (priv->phy_num == 0) {
		tlan_mii_read_reg(dev, phy, TLAN_TLPHY_CTL, &tlphy_ctl);
		tlphy_ctl |= TLAN_TC_INTEN;
		tlan_mii_write_reg(dev, phy, TLAN_TLPHY_CTL, tlphy_ctl);
		sio = tlan_dio_read8(dev->base_addr, TLAN_NET_SIO);
		sio |= TLAN_NET_SIO_MINTEN;
		tlan_dio_write8(dev->base_addr, TLAN_NET_SIO, sio);
	}

	if (status & MII_GS_LINK) {
		tlan_set_mac(dev, 0, dev->dev_addr);
		priv->phy_online = 1;
		outb((TLAN_HC_INT_ON >> 8), dev->base_addr + TLAN_HOST_CMD + 1);
		if (debug >= 1 && debug != TLAN_DEBUG_PROBE)
			outb((TLAN_HC_REQ_INT >> 8),
			     dev->base_addr + TLAN_HOST_CMD + 1);
		outl(priv->rx_list_dma, dev->base_addr + TLAN_CH_PARM);
		outl(TLAN_HC_GO | TLAN_HC_RT, dev->base_addr + TLAN_HOST_CMD);
		tlan_dio_write8(dev->base_addr, TLAN_LED_REG, TLAN_LED_LINK);
		netif_carrier_on(dev);
	} else {
		netdev_info(dev, "Link inactive, will retry in 10 secs...\n");
		tlan_set_timer(dev, (10*HZ), TLAN_TIMER_FINISH_RESET);
		return;
	}
	tlan_set_multicast_list(dev);

}