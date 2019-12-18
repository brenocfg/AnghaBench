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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct tlan_priv {int* phy; size_t phy_num; int /*<<< orphan*/  tlan_tqueue; } ;
struct net_device {int /*<<< orphan*/  name; scalar_t__ base_addr; } ;

/* Variables and functions */
 scalar_t__ TLAN_CH_PARM ; 
 int /*<<< orphan*/  TLAN_DBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  TLAN_DEBUG_GNRL ; 
 int /*<<< orphan*/  TLAN_HC_AD_RST ; 
 int TLAN_HI_IV_MASK ; 
 scalar_t__ TLAN_HOST_CMD ; 
 int /*<<< orphan*/  TLAN_NET_STS ; 
 int TLAN_NET_STS_MIRQ ; 
 int /*<<< orphan*/  TLAN_RECORD ; 
 int TLAN_TC_SWAPOL ; 
 int /*<<< orphan*/  TLAN_TLPHY_CTL ; 
 int /*<<< orphan*/  TLAN_TLPHY_STS ; 
 int TLAN_TS_POLOK ; 
 scalar_t__ debug ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int) ; 
 struct tlan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int tlan_dio_read8 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlan_dio_write8 (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tlan_mii_read_reg (struct net_device*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  tlan_mii_write_reg (struct net_device*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tlan_phy_print (struct net_device*) ; 
 int /*<<< orphan*/  tlan_read_and_clear_stats (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 tlan_handle_status_check(struct net_device *dev, u16 host_int)
{
	struct tlan_priv	*priv = netdev_priv(dev);
	u32		ack;
	u32		error;
	u8		net_sts;
	u32		phy;
	u16		tlphy_ctl;
	u16		tlphy_sts;

	ack = 1;
	if (host_int & TLAN_HI_IV_MASK) {
		netif_stop_queue(dev);
		error = inl(dev->base_addr + TLAN_CH_PARM);
		netdev_info(dev, "Adaptor Error = 0x%x\n", error);
		tlan_read_and_clear_stats(dev, TLAN_RECORD);
		outl(TLAN_HC_AD_RST, dev->base_addr + TLAN_HOST_CMD);

		schedule_work(&priv->tlan_tqueue);

		netif_wake_queue(dev);
		ack = 0;
	} else {
		TLAN_DBG(TLAN_DEBUG_GNRL, "%s: Status Check\n", dev->name);
		phy = priv->phy[priv->phy_num];

		net_sts = tlan_dio_read8(dev->base_addr, TLAN_NET_STS);
		if (net_sts) {
			tlan_dio_write8(dev->base_addr, TLAN_NET_STS, net_sts);
			TLAN_DBG(TLAN_DEBUG_GNRL, "%s:    Net_Sts = %x\n",
				 dev->name, (unsigned) net_sts);
		}
		if ((net_sts & TLAN_NET_STS_MIRQ) &&  (priv->phy_num == 0)) {
			tlan_mii_read_reg(dev, phy, TLAN_TLPHY_STS, &tlphy_sts);
			tlan_mii_read_reg(dev, phy, TLAN_TLPHY_CTL, &tlphy_ctl);
			if (!(tlphy_sts & TLAN_TS_POLOK) &&
			    !(tlphy_ctl & TLAN_TC_SWAPOL)) {
				tlphy_ctl |= TLAN_TC_SWAPOL;
				tlan_mii_write_reg(dev, phy, TLAN_TLPHY_CTL,
						   tlphy_ctl);
			} else if ((tlphy_sts & TLAN_TS_POLOK) &&
				   (tlphy_ctl & TLAN_TC_SWAPOL)) {
				tlphy_ctl &= ~TLAN_TC_SWAPOL;
				tlan_mii_write_reg(dev, phy, TLAN_TLPHY_CTL,
						   tlphy_ctl);
			}

			if (debug)
				tlan_phy_print(dev);
		}
	}

	return ack;

}