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
struct qlcnic_recv_context {struct qlcnic_host_sds_ring* sds_rings; } ;
struct qlcnic_host_tx_ring {int /*<<< orphan*/  napi; } ;
struct qlcnic_host_sds_ring {int /*<<< orphan*/  napi; } ;
struct qlcnic_adapter {int drv_sds_rings; int drv_tx_rings; struct qlcnic_host_tx_ring* tx_ring; TYPE_1__* ahw; struct qlcnic_recv_context* recv_ctx; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  diag_test; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NAPI_POLL_WEIGHT ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qlcnic_alloc_sds_rings (struct qlcnic_recv_context*,int) ; 
 scalar_t__ qlcnic_alloc_tx_rings (struct qlcnic_adapter*,struct net_device*) ; 
 scalar_t__ qlcnic_check_multi_tx (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_free_sds_rings (struct qlcnic_recv_context*) ; 
 int /*<<< orphan*/  qlcnic_poll ; 
 int /*<<< orphan*/  qlcnic_rx_poll ; 
 int /*<<< orphan*/  qlcnic_tx_poll ; 

int qlcnic_82xx_napi_add(struct qlcnic_adapter *adapter,
			 struct net_device *netdev)
{
	int ring;
	struct qlcnic_host_sds_ring *sds_ring;
	struct qlcnic_recv_context *recv_ctx = adapter->recv_ctx;
	struct qlcnic_host_tx_ring *tx_ring;

	if (qlcnic_alloc_sds_rings(recv_ctx, adapter->drv_sds_rings))
		return -ENOMEM;

	for (ring = 0; ring < adapter->drv_sds_rings; ring++) {
		sds_ring = &recv_ctx->sds_rings[ring];
		if (qlcnic_check_multi_tx(adapter) &&
		    !adapter->ahw->diag_test) {
			netif_napi_add(netdev, &sds_ring->napi, qlcnic_rx_poll,
				       NAPI_POLL_WEIGHT);
		} else {
			if (ring == (adapter->drv_sds_rings - 1))
				netif_napi_add(netdev, &sds_ring->napi,
					       qlcnic_poll,
					       NAPI_POLL_WEIGHT);
			else
				netif_napi_add(netdev, &sds_ring->napi,
					       qlcnic_rx_poll,
					       NAPI_POLL_WEIGHT);
		}
	}

	if (qlcnic_alloc_tx_rings(adapter, netdev)) {
		qlcnic_free_sds_rings(recv_ctx);
		return -ENOMEM;
	}

	if (qlcnic_check_multi_tx(adapter) && !adapter->ahw->diag_test) {
		for (ring = 0; ring < adapter->drv_tx_rings; ring++) {
			tx_ring = &adapter->tx_ring[ring];
			netif_tx_napi_add(netdev, &tx_ring->napi, qlcnic_tx_poll,
				       NAPI_POLL_WEIGHT);
		}
	}

	return 0;
}