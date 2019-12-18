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
struct netdata_local {int /*<<< orphan*/  clk; int /*<<< orphan*/  lock; int /*<<< orphan*/  net_base; int /*<<< orphan*/  napi; TYPE_1__* pdev; } ;
struct net_device {scalar_t__ phydev; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC_ENET_MAC1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC_ENET_MAC2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lpc_eth_reset (struct netdata_local*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct netdata_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_msg_ifdown (struct netdata_local*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc_eth_close(struct net_device *ndev)
{
	unsigned long flags;
	struct netdata_local *pldat = netdev_priv(ndev);

	if (netif_msg_ifdown(pldat))
		dev_dbg(&pldat->pdev->dev, "shutting down %s\n", ndev->name);

	napi_disable(&pldat->napi);
	netif_stop_queue(ndev);

	if (ndev->phydev)
		phy_stop(ndev->phydev);

	spin_lock_irqsave(&pldat->lock, flags);
	__lpc_eth_reset(pldat);
	netif_carrier_off(ndev);
	writel(0, LPC_ENET_MAC1(pldat->net_base));
	writel(0, LPC_ENET_MAC2(pldat->net_base));
	spin_unlock_irqrestore(&pldat->lock, flags);

	clk_disable_unprepare(pldat->clk);

	return 0;
}