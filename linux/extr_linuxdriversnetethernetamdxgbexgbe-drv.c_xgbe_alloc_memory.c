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
struct xgbe_desc_if {int (* alloc_ring_resources ) (struct xgbe_prv_data*) ;} ;
struct xgbe_prv_data {int /*<<< orphan*/  rx_buf_size; scalar_t__ new_rx_ring_count; scalar_t__ rx_ring_count; scalar_t__ new_tx_ring_count; scalar_t__ tx_ring_count; scalar_t__ tx_q_count; struct net_device* netdev; struct xgbe_desc_if desc_if; } ;
struct net_device {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int stub1 (struct xgbe_prv_data*) ; 
 int xgbe_alloc_channels (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_calc_rx_buf_size (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_free_memory (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_init_timers (struct xgbe_prv_data*) ; 

__attribute__((used)) static int xgbe_alloc_memory(struct xgbe_prv_data *pdata)
{
	struct xgbe_desc_if *desc_if = &pdata->desc_if;
	struct net_device *netdev = pdata->netdev;
	int ret;

	if (pdata->new_tx_ring_count) {
		pdata->tx_ring_count = pdata->new_tx_ring_count;
		pdata->tx_q_count = pdata->tx_ring_count;
		pdata->new_tx_ring_count = 0;
	}

	if (pdata->new_rx_ring_count) {
		pdata->rx_ring_count = pdata->new_rx_ring_count;
		pdata->new_rx_ring_count = 0;
	}

	/* Calculate the Rx buffer size before allocating rings */
	pdata->rx_buf_size = xgbe_calc_rx_buf_size(netdev, netdev->mtu);

	/* Allocate the channel and ring structures */
	ret = xgbe_alloc_channels(pdata);
	if (ret)
		return ret;

	/* Allocate the ring descriptors and buffers */
	ret = desc_if->alloc_ring_resources(pdata);
	if (ret)
		goto err_channels;

	/* Initialize the service and Tx timers */
	xgbe_init_timers(pdata);

	return 0;

err_channels:
	xgbe_free_memory(pdata);

	return ret;
}