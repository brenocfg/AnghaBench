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
struct net_device {scalar_t__ phydev; } ;
struct hix5hd2_priv {int /*<<< orphan*/  mac_core_clk; int /*<<< orphan*/  mac_ifc_clk; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hix5hd2_free_dma_desc_rings (struct hix5hd2_priv*) ; 
 int /*<<< orphan*/  hix5hd2_irq_disable (struct hix5hd2_priv*) ; 
 int /*<<< orphan*/  hix5hd2_port_disable (struct hix5hd2_priv*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct hix5hd2_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_disconnect (scalar_t__) ; 
 int /*<<< orphan*/  phy_stop (scalar_t__) ; 

__attribute__((used)) static int hix5hd2_net_close(struct net_device *dev)
{
	struct hix5hd2_priv *priv = netdev_priv(dev);

	hix5hd2_port_disable(priv);
	hix5hd2_irq_disable(priv);
	napi_disable(&priv->napi);
	netif_stop_queue(dev);
	hix5hd2_free_dma_desc_rings(priv);

	if (dev->phydev) {
		phy_stop(dev->phydev);
		phy_disconnect(dev->phydev);
	}

	clk_disable_unprepare(priv->mac_ifc_clk);
	clk_disable_unprepare(priv->mac_core_clk);

	return 0;
}