#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct ethtool_pauseparam {int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  rx_pause; scalar_t__ autoneg; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  rx_pause; } ;
struct TYPE_5__ {TYPE_1__ pause_config; } ;
struct TYPE_6__ {TYPE_2__ enet; } ;
struct bnad {TYPE_3__ bna; } ;

/* Variables and functions */
 struct bnad* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
bnad_get_pauseparam(struct net_device *netdev,
		    struct ethtool_pauseparam *pauseparam)
{
	struct bnad *bnad = netdev_priv(netdev);

	pauseparam->autoneg = 0;
	pauseparam->rx_pause = bnad->bna.enet.pause_config.rx_pause;
	pauseparam->tx_pause = bnad->bna.enet.pause_config.tx_pause;
}