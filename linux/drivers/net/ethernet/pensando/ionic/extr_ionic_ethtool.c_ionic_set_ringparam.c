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
struct ionic_lif {scalar_t__ ntxq_descs; scalar_t__ nrxq_descs; int /*<<< orphan*/  state; } ;
struct ethtool_ringparam {scalar_t__ tx_pending; scalar_t__ rx_pending; scalar_t__ rx_jumbo_pending; scalar_t__ rx_mini_pending; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  IONIC_LIF_QUEUE_RESET ; 
 int /*<<< orphan*/  IONIC_LIF_UP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ionic_open (struct net_device*) ; 
 int /*<<< orphan*/  ionic_stop (struct net_device*) ; 
 int /*<<< orphan*/  ionic_wait_for_bit (struct ionic_lif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_power_of_2 (scalar_t__) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct ionic_lif* netdev_priv (struct net_device*) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ionic_set_ringparam(struct net_device *netdev,
			       struct ethtool_ringparam *ring)
{
	struct ionic_lif *lif = netdev_priv(netdev);
	bool running;

	if (ring->rx_mini_pending || ring->rx_jumbo_pending) {
		netdev_info(netdev, "Changing jumbo or mini descriptors not supported\n");
		return -EINVAL;
	}

	if (!is_power_of_2(ring->tx_pending) ||
	    !is_power_of_2(ring->rx_pending)) {
		netdev_info(netdev, "Descriptor count must be a power of 2\n");
		return -EINVAL;
	}

	/* if nothing to do return success */
	if (ring->tx_pending == lif->ntxq_descs &&
	    ring->rx_pending == lif->nrxq_descs)
		return 0;

	if (!ionic_wait_for_bit(lif, IONIC_LIF_QUEUE_RESET))
		return -EBUSY;

	running = test_bit(IONIC_LIF_UP, lif->state);
	if (running)
		ionic_stop(netdev);

	lif->ntxq_descs = ring->tx_pending;
	lif->nrxq_descs = ring->rx_pending;

	if (running)
		ionic_open(netdev);
	clear_bit(IONIC_LIF_QUEUE_RESET, lif->state);

	return 0;
}