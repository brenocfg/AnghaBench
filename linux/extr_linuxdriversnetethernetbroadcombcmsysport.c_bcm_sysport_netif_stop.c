#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  phydev; } ;
struct TYPE_3__ {int /*<<< orphan*/  work; } ;
struct TYPE_4__ {TYPE_1__ dim; } ;
struct bcm_sysport_priv {TYPE_2__ dim; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_sysport_mask_all_intrs (struct bcm_sysport_priv*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct bcm_sysport_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm_sysport_netif_stop(struct net_device *dev)
{
	struct bcm_sysport_priv *priv = netdev_priv(dev);

	/* stop all software from updating hardware */
	netif_tx_disable(dev);
	napi_disable(&priv->napi);
	cancel_work_sync(&priv->dim.dim.work);
	phy_stop(dev->phydev);

	/* mask all interrupts */
	bcm_sysport_mask_all_intrs(priv);
}