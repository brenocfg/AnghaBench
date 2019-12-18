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
struct netdata_local {int /*<<< orphan*/  napi; int /*<<< orphan*/  clk; TYPE_1__* pdev; } ;
struct net_device {int /*<<< orphan*/  phydev; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __lpc_eth_init (struct netdata_local*) ; 
 int /*<<< orphan*/  __lpc_eth_reset (struct netdata_local*) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct netdata_local* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_ifup (struct netdata_local*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_resume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc_eth_open(struct net_device *ndev)
{
	struct netdata_local *pldat = netdev_priv(ndev);
	int ret;

	if (netif_msg_ifup(pldat))
		dev_dbg(&pldat->pdev->dev, "enabling %s\n", ndev->name);

	ret = clk_prepare_enable(pldat->clk);
	if (ret)
		return ret;

	/* Suspended PHY makes LPC ethernet core block, so resume now */
	phy_resume(ndev->phydev);

	/* Reset and initialize */
	__lpc_eth_reset(pldat);
	__lpc_eth_init(pldat);

	/* schedule a link state check */
	phy_start(ndev->phydev);
	netif_start_queue(ndev);
	napi_enable(&pldat->napi);

	return 0;
}