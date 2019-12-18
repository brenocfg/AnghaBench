#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stmmac_priv {TYPE_1__* plat; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ has_xgmac; } ;

/* Variables and functions */
 int REG_SPACE_SIZE ; 
 int XGMAC_REGSIZE ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int stmmac_ethtool_get_regs_len(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);

	if (priv->plat->has_xgmac)
		return XGMAC_REGSIZE * 4;
	return REG_SPACE_SIZE;
}