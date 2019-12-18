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
struct net_device {int dummy; } ;
struct hip04_priv {int /*<<< orphan*/  tx_coalesce_frames; int /*<<< orphan*/  tx_coalesce_usecs; } ;
struct ethtool_coalesce {int /*<<< orphan*/  tx_max_coalesced_frames; int /*<<< orphan*/  tx_coalesce_usecs; } ;

/* Variables and functions */
 struct hip04_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int hip04_get_coalesce(struct net_device *netdev,
			      struct ethtool_coalesce *ec)
{
	struct hip04_priv *priv = netdev_priv(netdev);

	ec->tx_coalesce_usecs = priv->tx_coalesce_usecs;
	ec->tx_max_coalesced_frames = priv->tx_coalesce_frames;

	return 0;
}