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
struct ethtool_pauseparam {scalar_t__ autoneg; scalar_t__ rx_pause; scalar_t__ tx_pause; } ;
struct TYPE_4__ {scalar_t__ rx_pause; scalar_t__ tx_pause; } ;
struct TYPE_6__ {TYPE_1__ pause_config; } ;
struct TYPE_5__ {TYPE_3__ enet; } ;
struct bnad {int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  bna_lock; TYPE_2__ bna; } ;
struct bna_pause_config {scalar_t__ rx_pause; scalar_t__ tx_pause; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int EINVAL ; 
 int /*<<< orphan*/  bna_enet_pause_config (TYPE_3__*,struct bna_pause_config*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct bnad* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
bnad_set_pauseparam(struct net_device *netdev,
		    struct ethtool_pauseparam *pauseparam)
{
	struct bnad *bnad = netdev_priv(netdev);
	struct bna_pause_config pause_config;
	unsigned long flags;

	if (pauseparam->autoneg == AUTONEG_ENABLE)
		return -EINVAL;

	mutex_lock(&bnad->conf_mutex);
	if (pauseparam->rx_pause != bnad->bna.enet.pause_config.rx_pause ||
	    pauseparam->tx_pause != bnad->bna.enet.pause_config.tx_pause) {
		pause_config.rx_pause = pauseparam->rx_pause;
		pause_config.tx_pause = pauseparam->tx_pause;
		spin_lock_irqsave(&bnad->bna_lock, flags);
		bna_enet_pause_config(&bnad->bna.enet, &pause_config);
		spin_unlock_irqrestore(&bnad->bna_lock, flags);
	}
	mutex_unlock(&bnad->conf_mutex);
	return 0;
}