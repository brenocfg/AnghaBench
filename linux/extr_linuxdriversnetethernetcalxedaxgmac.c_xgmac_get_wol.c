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
struct xgmac_priv {int /*<<< orphan*/  wolopts; int /*<<< orphan*/  device; } ;
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int supported; int /*<<< orphan*/  wolopts; } ;

/* Variables and functions */
 int WAKE_MAGIC ; 
 int WAKE_UCAST ; 
 scalar_t__ device_can_wakeup (int /*<<< orphan*/ ) ; 
 struct xgmac_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void xgmac_get_wol(struct net_device *dev,
			       struct ethtool_wolinfo *wol)
{
	struct xgmac_priv *priv = netdev_priv(dev);

	if (device_can_wakeup(priv->device)) {
		wol->supported = WAKE_MAGIC | WAKE_UCAST;
		wol->wolopts = priv->wolopts;
	}
}