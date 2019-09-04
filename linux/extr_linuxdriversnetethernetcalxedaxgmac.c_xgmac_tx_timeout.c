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
struct xgmac_priv {int /*<<< orphan*/  tx_timeout_work; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct xgmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xgmac_tx_timeout(struct net_device *dev)
{
	struct xgmac_priv *priv = netdev_priv(dev);
	schedule_work(&priv->tx_timeout_work);
}