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
struct ixgbe_ring {int /*<<< orphan*/  state; TYPE_1__* q_vector; } ;
struct ixgbe_adapter {struct ixgbe_ring** xdp_ring; struct ixgbe_ring** tx_ring; struct ixgbe_ring** rx_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  __IXGBE_TX_DISABLED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_configure_rx_ring (struct ixgbe_adapter*,struct ixgbe_ring*) ; 
 int /*<<< orphan*/  ixgbe_configure_tx_ring (struct ixgbe_adapter*,struct ixgbe_ring*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 

void ixgbe_txrx_ring_enable(struct ixgbe_adapter *adapter, int ring)
{
	struct ixgbe_ring *rx_ring, *tx_ring, *xdp_ring;

	rx_ring = adapter->rx_ring[ring];
	tx_ring = adapter->tx_ring[ring];
	xdp_ring = adapter->xdp_ring[ring];

	/* Rx/Tx/XDP Tx share the same napi context. */
	napi_enable(&rx_ring->q_vector->napi);

	ixgbe_configure_tx_ring(adapter, tx_ring);
	if (xdp_ring)
		ixgbe_configure_tx_ring(adapter, xdp_ring);
	ixgbe_configure_rx_ring(adapter, rx_ring);

	clear_bit(__IXGBE_TX_DISABLED, &tx_ring->state);
	if (xdp_ring)
		clear_bit(__IXGBE_TX_DISABLED, &xdp_ring->state);
}