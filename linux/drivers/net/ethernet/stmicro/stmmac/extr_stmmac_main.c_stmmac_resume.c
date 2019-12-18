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
struct stmmac_priv {int /*<<< orphan*/  phylink; int /*<<< orphan*/  device; int /*<<< orphan*/  lock; scalar_t__ mii; TYPE_1__* plat; scalar_t__ irq_wake; int /*<<< orphan*/  hw; } ;
struct net_device {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ clk_ptp_ref; scalar_t__ pclk; scalar_t__ stmmac_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_prepare_enable (scalar_t__) ; 
 struct net_device* dev_get_drvdata (struct device*) ; 
 scalar_t__ device_may_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  phylink_mac_change (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phylink_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinctrl_pm_select_default_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  stmmac_clear_descriptors (struct stmmac_priv*) ; 
 int /*<<< orphan*/  stmmac_enable_all_queues (struct stmmac_priv*) ; 
 int /*<<< orphan*/  stmmac_hw_setup (struct net_device*,int) ; 
 int /*<<< orphan*/  stmmac_init_coalesce (struct stmmac_priv*) ; 
 int /*<<< orphan*/  stmmac_mdio_reset (scalar_t__) ; 
 int /*<<< orphan*/  stmmac_pmt (struct stmmac_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmmac_reset_queues_param (struct stmmac_priv*) ; 
 int /*<<< orphan*/  stmmac_set_rx_mode (struct net_device*) ; 
 int /*<<< orphan*/  stmmac_start_all_queues (struct stmmac_priv*) ; 

int stmmac_resume(struct device *dev)
{
	struct net_device *ndev = dev_get_drvdata(dev);
	struct stmmac_priv *priv = netdev_priv(ndev);

	if (!netif_running(ndev))
		return 0;

	/* Power Down bit, into the PM register, is cleared
	 * automatically as soon as a magic packet or a Wake-up frame
	 * is received. Anyway, it's better to manually clear
	 * this bit because it can generate problems while resuming
	 * from another devices (e.g. serial console).
	 */
	if (device_may_wakeup(priv->device)) {
		mutex_lock(&priv->lock);
		stmmac_pmt(priv, priv->hw, 0);
		mutex_unlock(&priv->lock);
		priv->irq_wake = 0;
	} else {
		pinctrl_pm_select_default_state(priv->device);
		/* enable the clk previously disabled */
		clk_prepare_enable(priv->plat->stmmac_clk);
		clk_prepare_enable(priv->plat->pclk);
		if (priv->plat->clk_ptp_ref)
			clk_prepare_enable(priv->plat->clk_ptp_ref);
		/* reset the phy so that it's ready */
		if (priv->mii)
			stmmac_mdio_reset(priv->mii);
	}

	netif_device_attach(ndev);

	mutex_lock(&priv->lock);

	stmmac_reset_queues_param(priv);

	stmmac_clear_descriptors(priv);

	stmmac_hw_setup(ndev, false);
	stmmac_init_coalesce(priv);
	stmmac_set_rx_mode(ndev);

	stmmac_enable_all_queues(priv);

	stmmac_start_all_queues(priv);

	mutex_unlock(&priv->lock);

	if (!device_may_wakeup(priv->device)) {
		rtnl_lock();
		phylink_start(priv->phylink);
		rtnl_unlock();
	}

	phylink_mac_change(priv->phylink, true);

	return 0;
}