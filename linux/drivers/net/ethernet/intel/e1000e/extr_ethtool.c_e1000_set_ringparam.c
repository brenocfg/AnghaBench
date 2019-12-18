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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; scalar_t__ rx_jumbo_pending; scalar_t__ rx_mini_pending; } ;
struct e1000_ring {scalar_t__ count; } ;
struct e1000_adapter {scalar_t__ tx_ring_count; scalar_t__ rx_ring_count; int /*<<< orphan*/  state; struct e1000_ring* rx_ring; struct e1000_ring* tx_ring; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_MAX_RXD ; 
 int /*<<< orphan*/  E1000_MAX_TXD ; 
 int /*<<< orphan*/  E1000_MIN_RXD ; 
 int /*<<< orphan*/  E1000_MIN_TXD ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  REQ_RX_DESCRIPTOR_MULTIPLE ; 
 int /*<<< orphan*/  REQ_TX_DESCRIPTOR_MULTIPLE ; 
 int /*<<< orphan*/  __E1000_RESETTING ; 
 scalar_t__ clamp_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000e_down (struct e1000_adapter*,int) ; 
 int /*<<< orphan*/  e1000e_free_rx_resources (struct e1000_ring*) ; 
 int /*<<< orphan*/  e1000e_free_tx_resources (struct e1000_ring*) ; 
 int e1000e_setup_rx_resources (struct e1000_ring*) ; 
 int e1000e_setup_tx_resources (struct e1000_ring*) ; 
 int /*<<< orphan*/  e1000e_up (struct e1000_adapter*) ; 
 int /*<<< orphan*/  memcpy (struct e1000_ring*,struct e1000_ring*,int) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u32 ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  vfree (struct e1000_ring*) ; 
 struct e1000_ring* vmalloc (int) ; 

__attribute__((used)) static int e1000_set_ringparam(struct net_device *netdev,
			       struct ethtool_ringparam *ring)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_ring *temp_tx = NULL, *temp_rx = NULL;
	int err = 0, size = sizeof(struct e1000_ring);
	bool set_tx = false, set_rx = false;
	u16 new_rx_count, new_tx_count;

	if ((ring->rx_mini_pending) || (ring->rx_jumbo_pending))
		return -EINVAL;

	new_rx_count = clamp_t(u32, ring->rx_pending, E1000_MIN_RXD,
			       E1000_MAX_RXD);
	new_rx_count = ALIGN(new_rx_count, REQ_RX_DESCRIPTOR_MULTIPLE);

	new_tx_count = clamp_t(u32, ring->tx_pending, E1000_MIN_TXD,
			       E1000_MAX_TXD);
	new_tx_count = ALIGN(new_tx_count, REQ_TX_DESCRIPTOR_MULTIPLE);

	if ((new_tx_count == adapter->tx_ring_count) &&
	    (new_rx_count == adapter->rx_ring_count))
		/* nothing to do */
		return 0;

	while (test_and_set_bit(__E1000_RESETTING, &adapter->state))
		usleep_range(1000, 2000);

	if (!netif_running(adapter->netdev)) {
		/* Set counts now and allocate resources during open() */
		adapter->tx_ring->count = new_tx_count;
		adapter->rx_ring->count = new_rx_count;
		adapter->tx_ring_count = new_tx_count;
		adapter->rx_ring_count = new_rx_count;
		goto clear_reset;
	}

	set_tx = (new_tx_count != adapter->tx_ring_count);
	set_rx = (new_rx_count != adapter->rx_ring_count);

	/* Allocate temporary storage for ring updates */
	if (set_tx) {
		temp_tx = vmalloc(size);
		if (!temp_tx) {
			err = -ENOMEM;
			goto free_temp;
		}
	}
	if (set_rx) {
		temp_rx = vmalloc(size);
		if (!temp_rx) {
			err = -ENOMEM;
			goto free_temp;
		}
	}

	pm_runtime_get_sync(netdev->dev.parent);

	e1000e_down(adapter, true);

	/* We can't just free everything and then setup again, because the
	 * ISRs in MSI-X mode get passed pointers to the Tx and Rx ring
	 * structs.  First, attempt to allocate new resources...
	 */
	if (set_tx) {
		memcpy(temp_tx, adapter->tx_ring, size);
		temp_tx->count = new_tx_count;
		err = e1000e_setup_tx_resources(temp_tx);
		if (err)
			goto err_setup;
	}
	if (set_rx) {
		memcpy(temp_rx, adapter->rx_ring, size);
		temp_rx->count = new_rx_count;
		err = e1000e_setup_rx_resources(temp_rx);
		if (err)
			goto err_setup_rx;
	}

	/* ...then free the old resources and copy back any new ring data */
	if (set_tx) {
		e1000e_free_tx_resources(adapter->tx_ring);
		memcpy(adapter->tx_ring, temp_tx, size);
		adapter->tx_ring_count = new_tx_count;
	}
	if (set_rx) {
		e1000e_free_rx_resources(adapter->rx_ring);
		memcpy(adapter->rx_ring, temp_rx, size);
		adapter->rx_ring_count = new_rx_count;
	}

err_setup_rx:
	if (err && set_tx)
		e1000e_free_tx_resources(temp_tx);
err_setup:
	e1000e_up(adapter);
	pm_runtime_put_sync(netdev->dev.parent);
free_temp:
	vfree(temp_tx);
	vfree(temp_rx);
clear_reset:
	clear_bit(__E1000_RESETTING, &adapter->state);
	return err;
}