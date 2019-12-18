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
struct net_device {int dummy; } ;
struct ave_private {scalar_t__ base; int /*<<< orphan*/  phy_mode; } ;

/* Variables and functions */
 scalar_t__ AVE_CFGR ; 
 int AVE_CFGR_CHE ; 
 int AVE_CFGR_FLE ; 
 int AVE_CFGR_IPFCEN ; 
 int AVE_CFGR_MII ; 
 scalar_t__ AVE_GRR ; 
 int AVE_GRR_GRST ; 
 int AVE_GRR_PHYRST ; 
 scalar_t__ AVE_RSTCTRL ; 
 int AVE_RSTCTRL_RMIIRST ; 
 int /*<<< orphan*/  ave_irq_disable_all (struct net_device*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct ave_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_interface_mode_is_rgmii (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void ave_global_reset(struct net_device *ndev)
{
	struct ave_private *priv = netdev_priv(ndev);
	u32 val;

	/* set config register */
	val = AVE_CFGR_FLE | AVE_CFGR_IPFCEN | AVE_CFGR_CHE;
	if (!phy_interface_mode_is_rgmii(priv->phy_mode))
		val |= AVE_CFGR_MII;
	writel(val, priv->base + AVE_CFGR);

	/* reset RMII register */
	val = readl(priv->base + AVE_RSTCTRL);
	val &= ~AVE_RSTCTRL_RMIIRST;
	writel(val, priv->base + AVE_RSTCTRL);

	/* assert reset */
	writel(AVE_GRR_GRST | AVE_GRR_PHYRST, priv->base + AVE_GRR);
	msleep(20);

	/* 1st, negate PHY reset only */
	writel(AVE_GRR_GRST, priv->base + AVE_GRR);
	msleep(40);

	/* negate reset */
	writel(0, priv->base + AVE_GRR);
	msleep(40);

	/* negate RMII register */
	val = readl(priv->base + AVE_RSTCTRL);
	val |= AVE_RSTCTRL_RMIIRST;
	writel(val, priv->base + AVE_RSTCTRL);

	ave_irq_disable_all(ndev);
}