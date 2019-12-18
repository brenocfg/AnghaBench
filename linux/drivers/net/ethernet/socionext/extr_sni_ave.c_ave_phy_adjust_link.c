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
typedef  int /*<<< orphan*/  u16 ;
struct phy_device {scalar_t__ speed; int /*<<< orphan*/  advertising; scalar_t__ asym_pause; scalar_t__ pause; scalar_t__ duplex; } ;
struct net_device {struct phy_device* phydev; } ;
struct ave_private {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ AVE_LINKSEL ; 
 int AVE_LINKSEL_100M ; 
 scalar_t__ AVE_RXCR ; 
 int AVE_RXCR_FDUPEN ; 
 int AVE_RXCR_FLOCTR ; 
 int AVE_RXCR_RXEN ; 
 scalar_t__ AVE_TXCR ; 
 int AVE_TXCR_FLOCTR ; 
 int AVE_TXCR_TXSPD_100 ; 
 int AVE_TXCR_TXSPD_1G ; 
 int FLOW_CTRL_RX ; 
 int FLOW_CTRL_TX ; 
 int /*<<< orphan*/  LPA_PAUSE_ASYM ; 
 int /*<<< orphan*/  LPA_PAUSE_CAP ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 int /*<<< orphan*/  linkmode_adv_to_lcl_adv_t (int /*<<< orphan*/ ) ; 
 int mii_resolve_flowctrl_fdx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ave_private* netdev_priv (struct net_device*) ; 
 scalar_t__ phy_interface_is_rgmii (struct phy_device*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void ave_phy_adjust_link(struct net_device *ndev)
{
	struct ave_private *priv = netdev_priv(ndev);
	struct phy_device *phydev = ndev->phydev;
	u32 val, txcr, rxcr, rxcr_org;
	u16 rmt_adv = 0, lcl_adv = 0;
	u8 cap;

	/* set RGMII speed */
	val = readl(priv->base + AVE_TXCR);
	val &= ~(AVE_TXCR_TXSPD_100 | AVE_TXCR_TXSPD_1G);

	if (phy_interface_is_rgmii(phydev) && phydev->speed == SPEED_1000)
		val |= AVE_TXCR_TXSPD_1G;
	else if (phydev->speed == SPEED_100)
		val |= AVE_TXCR_TXSPD_100;

	writel(val, priv->base + AVE_TXCR);

	/* set RMII speed (100M/10M only) */
	if (!phy_interface_is_rgmii(phydev)) {
		val = readl(priv->base + AVE_LINKSEL);
		if (phydev->speed == SPEED_10)
			val &= ~AVE_LINKSEL_100M;
		else
			val |= AVE_LINKSEL_100M;
		writel(val, priv->base + AVE_LINKSEL);
	}

	/* check current RXCR/TXCR */
	rxcr = readl(priv->base + AVE_RXCR);
	txcr = readl(priv->base + AVE_TXCR);
	rxcr_org = rxcr;

	if (phydev->duplex) {
		rxcr |= AVE_RXCR_FDUPEN;

		if (phydev->pause)
			rmt_adv |= LPA_PAUSE_CAP;
		if (phydev->asym_pause)
			rmt_adv |= LPA_PAUSE_ASYM;

		lcl_adv = linkmode_adv_to_lcl_adv_t(phydev->advertising);
		cap = mii_resolve_flowctrl_fdx(lcl_adv, rmt_adv);
		if (cap & FLOW_CTRL_TX)
			txcr |= AVE_TXCR_FLOCTR;
		else
			txcr &= ~AVE_TXCR_FLOCTR;
		if (cap & FLOW_CTRL_RX)
			rxcr |= AVE_RXCR_FLOCTR;
		else
			rxcr &= ~AVE_RXCR_FLOCTR;
	} else {
		rxcr &= ~AVE_RXCR_FDUPEN;
		rxcr &= ~AVE_RXCR_FLOCTR;
		txcr &= ~AVE_TXCR_FLOCTR;
	}

	if (rxcr_org != rxcr) {
		/* disable Rx mac */
		writel(rxcr & ~AVE_RXCR_RXEN, priv->base + AVE_RXCR);
		/* change and enable TX/Rx mac */
		writel(txcr, priv->base + AVE_TXCR);
		writel(rxcr, priv->base + AVE_RXCR);
	}

	phy_print_status(phydev);
}