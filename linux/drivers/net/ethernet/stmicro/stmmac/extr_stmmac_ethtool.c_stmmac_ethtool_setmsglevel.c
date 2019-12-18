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
typedef  int /*<<< orphan*/  u32 ;
struct stmmac_priv {int /*<<< orphan*/  msg_enable; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct stmmac_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void stmmac_ethtool_setmsglevel(struct net_device *dev, u32 level)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	priv->msg_enable = level;

}