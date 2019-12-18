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
struct ixgbe_ring {TYPE_1__* q_vector; } ;
struct ixgbe_adapter {struct ixgbe_ring** xdp_ring; struct ixgbe_ring** tx_ring; struct ixgbe_ring** rx_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ixgbe_clean_rx_ring (struct ixgbe_ring*) ; 
 int /*<<< orphan*/  ixgbe_clean_tx_ring (struct ixgbe_ring*) ; 
 int /*<<< orphan*/  ixgbe_disable_rxr_hw (struct ixgbe_adapter*,struct ixgbe_ring*) ; 
 int /*<<< orphan*/  ixgbe_disable_txr (struct ixgbe_adapter*,struct ixgbe_ring*) ; 
 int /*<<< orphan*/  ixgbe_reset_rxr_stats (struct ixgbe_ring*) ; 
 int /*<<< orphan*/  ixgbe_reset_txr_stats (struct ixgbe_ring*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void ixgbe_txrx_ring_disable(struct ixgbe_adapter *adapter, int ring)
{
	struct ixgbe_ring *rx_ring, *tx_ring, *xdp_ring;

	rx_ring = adapter->rx_ring[ring];
	tx_ring = adapter->tx_ring[ring];
	xdp_ring = adapter->xdp_ring[ring];

	ixgbe_disable_txr(adapter, tx_ring);
	if (xdp_ring)
		ixgbe_disable_txr(adapter, xdp_ring);
	ixgbe_disable_rxr_hw(adapter, rx_ring);

	if (xdp_ring)
		synchronize_rcu();

	/* Rx/Tx/XDP Tx share the same napi context. */
	napi_disable(&rx_ring->q_vector->napi);

	ixgbe_clean_tx_ring(tx_ring);
	if (xdp_ring)
		ixgbe_clean_tx_ring(xdp_ring);
	ixgbe_clean_rx_ring(rx_ring);

	ixgbe_reset_txr_stats(tx_ring);
	if (xdp_ring)
		ixgbe_reset_txr_stats(xdp_ring);
	ixgbe_reset_rxr_stats(rx_ring);
}