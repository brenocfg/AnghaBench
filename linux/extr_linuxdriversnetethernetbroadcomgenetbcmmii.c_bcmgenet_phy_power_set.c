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
struct bcmgenet_priv {int dummy; } ;

/* Variables and functions */
 int EXT_CFG_IDDQ_BIAS ; 
 int EXT_CFG_PWR_DOWN ; 
 int EXT_CK25_DIS ; 
 int /*<<< orphan*/  EXT_GPHY_CTRL ; 
 int EXT_GPHY_RESET ; 
 scalar_t__ GENET_IS_V4 (struct bcmgenet_priv*) ; 
 int bcmgenet_ext_readl (struct bcmgenet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcmgenet_ext_writel (struct bcmgenet_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct bcmgenet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

void bcmgenet_phy_power_set(struct net_device *dev, bool enable)
{
	struct bcmgenet_priv *priv = netdev_priv(dev);
	u32 reg = 0;

	/* EXT_GPHY_CTRL is only valid for GENETv4 and onward */
	if (GENET_IS_V4(priv)) {
		reg = bcmgenet_ext_readl(priv, EXT_GPHY_CTRL);
		if (enable) {
			reg &= ~EXT_CK25_DIS;
			bcmgenet_ext_writel(priv, reg, EXT_GPHY_CTRL);
			mdelay(1);

			reg &= ~(EXT_CFG_IDDQ_BIAS | EXT_CFG_PWR_DOWN);
			reg |= EXT_GPHY_RESET;
			bcmgenet_ext_writel(priv, reg, EXT_GPHY_CTRL);
			mdelay(1);

			reg &= ~EXT_GPHY_RESET;
		} else {
			reg |= EXT_CFG_IDDQ_BIAS | EXT_CFG_PWR_DOWN |
			       EXT_GPHY_RESET;
			bcmgenet_ext_writel(priv, reg, EXT_GPHY_CTRL);
			mdelay(1);
			reg |= EXT_CK25_DIS;
		}
		bcmgenet_ext_writel(priv, reg, EXT_GPHY_CTRL);
		udelay(60);
	} else {
		mdelay(1);
	}
}