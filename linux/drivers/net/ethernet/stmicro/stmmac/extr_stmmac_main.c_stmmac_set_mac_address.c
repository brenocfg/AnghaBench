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
struct stmmac_priv {int /*<<< orphan*/  hw; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int eth_mac_addr (struct net_device*,void*) ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stmmac_set_umac_addr (struct stmmac_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stmmac_set_mac_address(struct net_device *ndev, void *addr)
{
	struct stmmac_priv *priv = netdev_priv(ndev);
	int ret = 0;

	ret = eth_mac_addr(ndev, addr);
	if (ret)
		return ret;

	stmmac_set_umac_addr(priv, priv->hw, ndev->dev_addr, 0);

	return ret;
}