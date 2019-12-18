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
struct qlcnic_adapter {scalar_t__ is_up; int drv_sds_rings; int flags; int drv_tx_rings; struct qlcnic_host_tx_ring* tx_ring; TYPE_1__* ahw; struct qlcnic_recv_context* recv_ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  diag_test; } ;

/* Variables and functions */
 scalar_t__ QLCNIC_ADAPTER_UP_MAGIC ; 
 int QLCNIC_MSIX_ENABLED ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 scalar_t__ qlcnic_check_multi_tx (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_enable_sds_intr (struct qlcnic_adapter*,struct qlcnic_host_sds_ring*) ; 
 int /*<<< orphan*/  qlcnic_enable_tx_intr (struct qlcnic_adapter*,struct qlcnic_host_tx_ring*) ; 

void qlcnic_82xx_napi_enable(struct qlcnic_adapter *adapter)
{
	int ring;
	struct qlcnic_host_sds_ring *sds_ring;
	struct qlcnic_host_tx_ring *tx_ring;
	struct qlcnic_recv_context *recv_ctx = adapter->recv_ctx;

	if (adapter->is_up != QLCNIC_ADAPTER_UP_MAGIC)
		return;

	for (ring = 0; ring < adapter->drv_sds_rings; ring++) {
		sds_ring = &recv_ctx->sds_rings[ring];
		napi_enable(&sds_ring->napi);
		qlcnic_enable_sds_intr(adapter, sds_ring);
	}

	if (qlcnic_check_multi_tx(adapter) &&
	    (adapter->flags & QLCNIC_MSIX_ENABLED) &&
	    !adapter->ahw->diag_test) {
		for (ring = 0; ring < adapter->drv_tx_rings; ring++) {
			tx_ring = &adapter->tx_ring[ring];
			napi_enable(&tx_ring->napi);
			qlcnic_enable_tx_intr(adapter, tx_ring);
		}
	}
}