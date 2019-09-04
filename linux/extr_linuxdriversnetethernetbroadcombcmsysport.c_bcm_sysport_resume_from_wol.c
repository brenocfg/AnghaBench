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
typedef  int u32 ;
struct bcm_sysport_priv {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int INTRL2_0_BRCM_MATCH_TAG ; 
 int INTRL2_0_MPD ; 
 int /*<<< orphan*/  INTRL2_CPU_STATUS ; 
 int RXCHK_BRCM_TAG_EN ; 
 int RXCHK_BRCM_TAG_MATCH_MASK ; 
 int RXCHK_BRCM_TAG_MATCH_SHIFT ; 
 int /*<<< orphan*/  RXCHK_BRCM_TAG_MATCH_STATUS ; 
 int /*<<< orphan*/  RXCHK_CONTROL ; 
 int RXCHK_EN ; 
 int intrl2_0_readl (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpd_enable_set (struct bcm_sysport_priv*,int) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  netif_dbg (struct bcm_sysport_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int rxchk_readl (struct bcm_sysport_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxchk_writel (struct bcm_sysport_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wol ; 

__attribute__((used)) static void bcm_sysport_resume_from_wol(struct bcm_sysport_priv *priv)
{
	u32 reg;

	/* Disable RXCHK, active filters and Broadcom tag matching */
	reg = rxchk_readl(priv, RXCHK_CONTROL);
	reg &= ~(RXCHK_BRCM_TAG_MATCH_MASK <<
		 RXCHK_BRCM_TAG_MATCH_SHIFT | RXCHK_EN | RXCHK_BRCM_TAG_EN);
	rxchk_writel(priv, reg, RXCHK_CONTROL);

	/* Clear the MagicPacket detection logic */
	mpd_enable_set(priv, false);

	reg = intrl2_0_readl(priv, INTRL2_CPU_STATUS);
	if (reg & INTRL2_0_MPD)
		netdev_info(priv->netdev, "Wake-on-LAN (MPD) interrupt!\n");

	if (reg & INTRL2_0_BRCM_MATCH_TAG) {
		reg = rxchk_readl(priv, RXCHK_BRCM_TAG_MATCH_STATUS) &
				  RXCHK_BRCM_TAG_MATCH_MASK;
		netdev_info(priv->netdev,
			    "Wake-on-LAN (filters 0x%02x) interrupt!\n", reg);
	}

	netif_dbg(priv, wol, priv->netdev, "resumed from WOL\n");
}