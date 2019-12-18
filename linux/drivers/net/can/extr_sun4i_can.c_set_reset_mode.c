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
struct sun4ican_priv {scalar_t__ base; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int SUN4I_MODE_MAX_RETRIES ; 
 int SUN4I_MSEL_RESET_MODE ; 
 scalar_t__ SUN4I_REG_MSEL_ADDR ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct sun4ican_priv* netdev_priv (struct net_device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int set_reset_mode(struct net_device *dev)
{
	struct sun4ican_priv *priv = netdev_priv(dev);
	int retry = SUN4I_MODE_MAX_RETRIES;
	u32 mod_reg_val = 0;

	do {
		mod_reg_val = readl(priv->base + SUN4I_REG_MSEL_ADDR);
		mod_reg_val |= SUN4I_MSEL_RESET_MODE;
		writel(mod_reg_val, priv->base + SUN4I_REG_MSEL_ADDR);
	} while (retry-- && !(mod_reg_val & SUN4I_MSEL_RESET_MODE));

	if (!(readl(priv->base + SUN4I_REG_MSEL_ADDR) &
	      SUN4I_MSEL_RESET_MODE)) {
		netdev_err(dev, "setting controller into reset mode failed!\n");
		return -ETIMEDOUT;
	}

	return 0;
}