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
struct ravb_private {int wol_enabled; TYPE_1__* pdev; } ;
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int wolopts; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int WAKE_MAGIC ; 
 int /*<<< orphan*/  device_set_wakeup_enable (int /*<<< orphan*/ *,int) ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ravb_set_wol(struct net_device *ndev, struct ethtool_wolinfo *wol)
{
	struct ravb_private *priv = netdev_priv(ndev);

	if (wol->wolopts & ~WAKE_MAGIC)
		return -EOPNOTSUPP;

	priv->wol_enabled = !!(wol->wolopts & WAKE_MAGIC);

	device_set_wakeup_enable(&priv->pdev->dev, priv->wol_enabled);

	return 0;
}