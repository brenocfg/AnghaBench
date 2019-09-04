#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  dev; TYPE_2__* phydev; } ;
struct fec_enet_private {int quirks; int wol_flag; TYPE_1__* pdev; int /*<<< orphan*/  napi; } ;
struct TYPE_5__ {scalar_t__ drv; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int FEC_QUIRK_ERR006687 ; 
 int FEC_WOL_FLAG_ENABLE ; 
 int /*<<< orphan*/  device_set_wakeup_enable (int /*<<< orphan*/ *,int) ; 
 int fec_enet_alloc_buffers (struct net_device*) ; 
 int fec_enet_clk_enable (struct net_device*,int) ; 
 int /*<<< orphan*/  fec_enet_free_buffers (struct net_device*) ; 
 int fec_enet_mii_probe (struct net_device*) ; 
 int /*<<< orphan*/  fec_restart (struct net_device*) ; 
 int /*<<< orphan*/  imx6q_cpuidle_fec_irqs_used () ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  phy_reset_after_clk_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  phy_start (TYPE_2__*) ; 
 int /*<<< orphan*/  pinctrl_pm_select_default_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pinctrl_pm_select_sleep_state (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fec_enet_open(struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	int ret;
	bool reset_again;

	ret = pm_runtime_get_sync(&fep->pdev->dev);
	if (ret < 0)
		return ret;

	pinctrl_pm_select_default_state(&fep->pdev->dev);
	ret = fec_enet_clk_enable(ndev, true);
	if (ret)
		goto clk_enable;

	/* During the first fec_enet_open call the PHY isn't probed at this
	 * point. Therefore the phy_reset_after_clk_enable() call within
	 * fec_enet_clk_enable() fails. As we need this reset in order to be
	 * sure the PHY is working correctly we check if we need to reset again
	 * later when the PHY is probed
	 */
	if (ndev->phydev && ndev->phydev->drv)
		reset_again = false;
	else
		reset_again = true;

	/* I should reset the ring buffers here, but I don't yet know
	 * a simple way to do that.
	 */

	ret = fec_enet_alloc_buffers(ndev);
	if (ret)
		goto err_enet_alloc;

	/* Init MAC prior to mii bus probe */
	fec_restart(ndev);

	/* Probe and connect to PHY when open the interface */
	ret = fec_enet_mii_probe(ndev);
	if (ret)
		goto err_enet_mii_probe;

	/* Call phy_reset_after_clk_enable() again if it failed during
	 * phy_reset_after_clk_enable() before because the PHY wasn't probed.
	 */
	if (reset_again)
		phy_reset_after_clk_enable(ndev->phydev);

	if (fep->quirks & FEC_QUIRK_ERR006687)
		imx6q_cpuidle_fec_irqs_used();

	napi_enable(&fep->napi);
	phy_start(ndev->phydev);
	netif_tx_start_all_queues(ndev);

	device_set_wakeup_enable(&ndev->dev, fep->wol_flag &
				 FEC_WOL_FLAG_ENABLE);

	return 0;

err_enet_mii_probe:
	fec_enet_free_buffers(ndev);
err_enet_alloc:
	fec_enet_clk_enable(ndev, false);
clk_enable:
	pm_runtime_mark_last_busy(&fep->pdev->dev);
	pm_runtime_put_autosuspend(&fep->pdev->dev);
	pinctrl_pm_select_sleep_state(&fep->pdev->dev);
	return ret;
}