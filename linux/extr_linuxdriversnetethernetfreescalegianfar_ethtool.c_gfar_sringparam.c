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
struct net_device {int flags; } ;
struct gfar_private {int num_rx_queues; int num_tx_queues; int /*<<< orphan*/  state; TYPE_2__** tx_queue; TYPE_1__** rx_queue; } ;
struct ethtool_ringparam {scalar_t__ rx_pending; scalar_t__ tx_pending; } ;
struct TYPE_4__ {scalar_t__ tx_ring_size; } ;
struct TYPE_3__ {scalar_t__ rx_ring_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFAR_RESETTING ; 
 scalar_t__ GFAR_RX_MAX_RING_SIZE ; 
 scalar_t__ GFAR_TX_MAX_RING_SIZE ; 
 int IFF_UP ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  is_power_of_2 (scalar_t__) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 
 int startup_gfar (struct net_device*) ; 
 int /*<<< orphan*/  stop_gfar (struct net_device*) ; 
 scalar_t__ test_and_set_bit_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gfar_sringparam(struct net_device *dev,
			   struct ethtool_ringparam *rvals)
{
	struct gfar_private *priv = netdev_priv(dev);
	int err = 0, i;

	if (rvals->rx_pending > GFAR_RX_MAX_RING_SIZE)
		return -EINVAL;

	if (!is_power_of_2(rvals->rx_pending)) {
		netdev_err(dev, "Ring sizes must be a power of 2\n");
		return -EINVAL;
	}

	if (rvals->tx_pending > GFAR_TX_MAX_RING_SIZE)
		return -EINVAL;

	if (!is_power_of_2(rvals->tx_pending)) {
		netdev_err(dev, "Ring sizes must be a power of 2\n");
		return -EINVAL;
	}

	while (test_and_set_bit_lock(GFAR_RESETTING, &priv->state))
		cpu_relax();

	if (dev->flags & IFF_UP)
		stop_gfar(dev);

	/* Change the sizes */
	for (i = 0; i < priv->num_rx_queues; i++)
		priv->rx_queue[i]->rx_ring_size = rvals->rx_pending;

	for (i = 0; i < priv->num_tx_queues; i++)
		priv->tx_queue[i]->tx_ring_size = rvals->tx_pending;

	/* Rebuild the rings with the new size */
	if (dev->flags & IFF_UP)
		err = startup_gfar(dev);

	clear_bit_unlock(GFAR_RESETTING, &priv->state);

	return err;
}