#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_device {TYPE_2__* phydev; } ;
struct mtk_mac {int /*<<< orphan*/  of_node; int /*<<< orphan*/  id; TYPE_3__* hw; int /*<<< orphan*/  trgmii; } ;
struct TYPE_8__ {TYPE_1__* soc; int /*<<< orphan*/  state; } ;
struct TYPE_7__ {int advertising; scalar_t__ link; scalar_t__ asym_pause; scalar_t__ pause; scalar_t__ duplex; int /*<<< orphan*/  speed; } ;
struct TYPE_6__ {int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Pause ; 
 int /*<<< orphan*/  ADVERTISE_PAUSE_ASYM ; 
 int /*<<< orphan*/  ADVERTISE_PAUSE_CAP ; 
 int FLOW_CTRL_RX ; 
 int FLOW_CTRL_TX ; 
 int /*<<< orphan*/  LPA_PAUSE_ASYM ; 
 int /*<<< orphan*/  LPA_PAUSE_CAP ; 
 int MAC_MCR_BACKOFF_EN ; 
 int MAC_MCR_BACKPR_EN ; 
 int MAC_MCR_FORCE_DPX ; 
 int MAC_MCR_FORCE_LINK ; 
 int MAC_MCR_FORCE_MODE ; 
 int MAC_MCR_FORCE_RX_FC ; 
 int MAC_MCR_FORCE_TX_FC ; 
 int MAC_MCR_IPG_CFG ; 
 int MAC_MCR_MAX_RX_1536 ; 
 int MAC_MCR_RX_EN ; 
 int MAC_MCR_SPEED_100 ; 
 int MAC_MCR_SPEED_1000 ; 
 int MAC_MCR_TX_EN ; 
 int /*<<< orphan*/  MTK_GMAC1_TRGMII ; 
 scalar_t__ MTK_HAS_CAPS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTK_MAC_MCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTK_RESETTING ; 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int /*<<< orphan*/  link ; 
 int mii_resolve_flowctrl_fdx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_gmac0_rgmii_adjust (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_w32 (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 struct mtk_mac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (TYPE_3__*,int /*<<< orphan*/ ,struct net_device*,char*,char*,char*) ; 
 int /*<<< orphan*/  of_phy_is_fixed_link (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_print_status (TYPE_2__*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_phy_link_adjust(struct net_device *dev)
{
	struct mtk_mac *mac = netdev_priv(dev);
	u16 lcl_adv = 0, rmt_adv = 0;
	u8 flowctrl;
	u32 mcr = MAC_MCR_MAX_RX_1536 | MAC_MCR_IPG_CFG |
		  MAC_MCR_FORCE_MODE | MAC_MCR_TX_EN |
		  MAC_MCR_RX_EN | MAC_MCR_BACKOFF_EN |
		  MAC_MCR_BACKPR_EN;

	if (unlikely(test_bit(MTK_RESETTING, &mac->hw->state)))
		return;

	switch (dev->phydev->speed) {
	case SPEED_1000:
		mcr |= MAC_MCR_SPEED_1000;
		break;
	case SPEED_100:
		mcr |= MAC_MCR_SPEED_100;
		break;
	};

	if (MTK_HAS_CAPS(mac->hw->soc->caps, MTK_GMAC1_TRGMII) &&
	    !mac->id && !mac->trgmii)
		mtk_gmac0_rgmii_adjust(mac->hw, dev->phydev->speed);

	if (dev->phydev->link)
		mcr |= MAC_MCR_FORCE_LINK;

	if (dev->phydev->duplex) {
		mcr |= MAC_MCR_FORCE_DPX;

		if (dev->phydev->pause)
			rmt_adv = LPA_PAUSE_CAP;
		if (dev->phydev->asym_pause)
			rmt_adv |= LPA_PAUSE_ASYM;

		if (dev->phydev->advertising & ADVERTISED_Pause)
			lcl_adv |= ADVERTISE_PAUSE_CAP;
		if (dev->phydev->advertising & ADVERTISED_Asym_Pause)
			lcl_adv |= ADVERTISE_PAUSE_ASYM;

		flowctrl = mii_resolve_flowctrl_fdx(lcl_adv, rmt_adv);

		if (flowctrl & FLOW_CTRL_TX)
			mcr |= MAC_MCR_FORCE_TX_FC;
		if (flowctrl & FLOW_CTRL_RX)
			mcr |= MAC_MCR_FORCE_RX_FC;

		netif_dbg(mac->hw, link, dev, "rx pause %s, tx pause %s\n",
			  flowctrl & FLOW_CTRL_RX ? "enabled" : "disabled",
			  flowctrl & FLOW_CTRL_TX ? "enabled" : "disabled");
	}

	mtk_w32(mac->hw, mcr, MTK_MAC_MCR(mac->id));

	if (dev->phydev->link)
		netif_carrier_on(dev);
	else
		netif_carrier_off(dev);

	if (!of_phy_is_fixed_link(mac->of_node))
		phy_print_status(dev->phydev);
}