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
struct sun4ican_priv {int /*<<< orphan*/  clk; scalar_t__ base; } ;
struct net_device {int dummy; } ;
struct can_berr_counter {int txerr; int rxerr; } ;

/* Variables and functions */
 scalar_t__ SUN4I_REG_ERRC_ADDR ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device const*,char*) ; 
 struct sun4ican_priv* netdev_priv (struct net_device const*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int sun4ican_get_berr_counter(const struct net_device *dev,
				     struct can_berr_counter *bec)
{
	struct sun4ican_priv *priv = netdev_priv(dev);
	u32 errors;
	int err;

	err = clk_prepare_enable(priv->clk);
	if (err) {
		netdev_err(dev, "could not enable clock\n");
		return err;
	}

	errors = readl(priv->base + SUN4I_REG_ERRC_ADDR);

	bec->txerr = errors & 0xFF;
	bec->rxerr = (errors >> 16) & 0xFF;

	clk_disable_unprepare(priv->clk);

	return 0;
}