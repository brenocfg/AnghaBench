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
struct net_device {int /*<<< orphan*/  phydev; } ;
struct fec_enet_private {int quirks; TYPE_1__* pdev; int /*<<< orphan*/  napi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int FEC_QUIRK_ERR006687 ; 
 int /*<<< orphan*/  fec_enet_clk_enable (struct net_device*,int) ; 
 int /*<<< orphan*/  fec_enet_free_buffers (struct net_device*) ; 
 int /*<<< orphan*/  fec_enet_update_ethtool_stats (struct net_device*) ; 
 int /*<<< orphan*/  fec_stop (struct net_device*) ; 
 int /*<<< orphan*/  imx6q_cpuidle_fec_irqs_unused () ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_device_present (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinctrl_pm_select_sleep_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fec_enet_close(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);

	phy_stop(ndev->phydev);

	if (netif_device_present(ndev)) {
		napi_disable(&fep->napi);
		netif_tx_disable(ndev);
		fec_stop(ndev);
	}

	phy_disconnect(ndev->phydev);

	if (fep->quirks & FEC_QUIRK_ERR006687)
		imx6q_cpuidle_fec_irqs_unused();

	fec_enet_update_ethtool_stats(ndev);

	fec_enet_clk_enable(ndev, false);
	pinctrl_pm_select_sleep_state(&fep->pdev->dev);
	pm_runtime_mark_last_busy(&fep->pdev->dev);
	pm_runtime_put_autosuspend(&fep->pdev->dev);

	fec_enet_free_buffers(ndev);

	return 0;
}