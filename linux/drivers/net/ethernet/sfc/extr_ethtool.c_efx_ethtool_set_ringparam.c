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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {scalar_t__ tx_pending; int /*<<< orphan*/  rx_pending; scalar_t__ rx_jumbo_pending; scalar_t__ rx_mini_pending; } ;
struct efx_nic {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_MAX_DMAQ_SIZE ; 
 int /*<<< orphan*/  EFX_RXQ_MIN_ENT ; 
 scalar_t__ EFX_TXQ_MAX_ENT (struct efx_nic*) ; 
 int /*<<< orphan*/  EFX_TXQ_MIN_ENT (struct efx_nic*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  drv ; 
 int efx_realloc_channels (struct efx_nic*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ max (scalar_t__,int /*<<< orphan*/ ) ; 
 struct efx_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_warn (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int efx_ethtool_set_ringparam(struct net_device *net_dev,
				     struct ethtool_ringparam *ring)
{
	struct efx_nic *efx = netdev_priv(net_dev);
	u32 txq_entries;

	if (ring->rx_mini_pending || ring->rx_jumbo_pending ||
	    ring->rx_pending > EFX_MAX_DMAQ_SIZE ||
	    ring->tx_pending > EFX_TXQ_MAX_ENT(efx))
		return -EINVAL;

	if (ring->rx_pending < EFX_RXQ_MIN_ENT) {
		netif_err(efx, drv, efx->net_dev,
			  "RX queues cannot be smaller than %u\n",
			  EFX_RXQ_MIN_ENT);
		return -EINVAL;
	}

	txq_entries = max(ring->tx_pending, EFX_TXQ_MIN_ENT(efx));
	if (txq_entries != ring->tx_pending)
		netif_warn(efx, drv, efx->net_dev,
			   "increasing TX queue size to minimum of %u\n",
			   txq_entries);

	return efx_realloc_channels(efx, ring->rx_pending, txq_entries);
}