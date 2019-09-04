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
struct hisi_femac_priv {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_ENA_PORT0 ; 
 int /*<<< orphan*/  hisi_femac_free_skb_rings (struct hisi_femac_priv*) ; 
 int /*<<< orphan*/  hisi_femac_irq_disable (struct hisi_femac_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct hisi_femac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (scalar_t__) ; 

__attribute__((used)) static int hisi_femac_net_close(struct net_device *dev)
{
	struct hisi_femac_priv *priv = netdev_priv(dev);

	hisi_femac_irq_disable(priv, IRQ_ENA_PORT0);

	if (dev->phydev)
		phy_stop(dev->phydev);

	netif_stop_queue(dev);
	napi_disable(&priv->napi);

	hisi_femac_free_skb_rings(priv);

	return 0;
}