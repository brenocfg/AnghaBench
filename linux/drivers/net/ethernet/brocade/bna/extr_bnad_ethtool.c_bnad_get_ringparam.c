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
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_max_pending; } ;
struct bnad {int /*<<< orphan*/  txq_depth; int /*<<< orphan*/  rxq_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNAD_MAX_RXQ_DEPTH ; 
 int /*<<< orphan*/  BNAD_MAX_TXQ_DEPTH ; 
 struct bnad* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
bnad_get_ringparam(struct net_device *netdev,
		   struct ethtool_ringparam *ringparam)
{
	struct bnad *bnad = netdev_priv(netdev);

	ringparam->rx_max_pending = BNAD_MAX_RXQ_DEPTH;
	ringparam->tx_max_pending = BNAD_MAX_TXQ_DEPTH;

	ringparam->rx_pending = bnad->rxq_depth;
	ringparam->tx_pending = bnad->txq_depth;
}