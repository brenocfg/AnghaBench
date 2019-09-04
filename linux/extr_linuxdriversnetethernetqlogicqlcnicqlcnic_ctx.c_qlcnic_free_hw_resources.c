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
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_recv_context {struct qlcnic_host_sds_ring* sds_rings; struct qlcnic_host_rds_ring* rds_rings; } ;
struct qlcnic_host_tx_ring {int /*<<< orphan*/ * desc_head; int /*<<< orphan*/  phys_addr; int /*<<< orphan*/ * hw_consumer; int /*<<< orphan*/  hw_cons_phys_addr; } ;
struct qlcnic_host_sds_ring {int /*<<< orphan*/ * desc_head; int /*<<< orphan*/  phys_addr; } ;
struct qlcnic_host_rds_ring {int /*<<< orphan*/ * desc_head; int /*<<< orphan*/  phys_addr; } ;
struct qlcnic_adapter {int drv_tx_rings; int max_rds_rings; int drv_sds_rings; TYPE_1__* pdev; struct qlcnic_host_tx_ring* tx_ring; struct qlcnic_recv_context* recv_ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int RCV_DESC_RINGSIZE (struct qlcnic_host_rds_ring*) ; 
 int STATUS_DESC_RINGSIZE (struct qlcnic_host_sds_ring*) ; 
 int TX_DESC_RINGSIZE (struct qlcnic_host_tx_ring*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void qlcnic_free_hw_resources(struct qlcnic_adapter *adapter)
{
	struct qlcnic_recv_context *recv_ctx;
	struct qlcnic_host_rds_ring *rds_ring;
	struct qlcnic_host_sds_ring *sds_ring;
	struct qlcnic_host_tx_ring *tx_ring;
	int ring;

	recv_ctx = adapter->recv_ctx;

	for (ring = 0; ring < adapter->drv_tx_rings; ring++) {
		tx_ring = &adapter->tx_ring[ring];
		if (tx_ring->hw_consumer != NULL) {
			dma_free_coherent(&adapter->pdev->dev, sizeof(u32),
					  tx_ring->hw_consumer,
					  tx_ring->hw_cons_phys_addr);

			tx_ring->hw_consumer = NULL;
		}

		if (tx_ring->desc_head != NULL) {
			dma_free_coherent(&adapter->pdev->dev,
					  TX_DESC_RINGSIZE(tx_ring),
					  tx_ring->desc_head,
					  tx_ring->phys_addr);
			tx_ring->desc_head = NULL;
		}
	}

	for (ring = 0; ring < adapter->max_rds_rings; ring++) {
		rds_ring = &recv_ctx->rds_rings[ring];

		if (rds_ring->desc_head != NULL) {
			dma_free_coherent(&adapter->pdev->dev,
					RCV_DESC_RINGSIZE(rds_ring),
					rds_ring->desc_head,
					rds_ring->phys_addr);
			rds_ring->desc_head = NULL;
		}
	}

	for (ring = 0; ring < adapter->drv_sds_rings; ring++) {
		sds_ring = &recv_ctx->sds_rings[ring];

		if (sds_ring->desc_head != NULL) {
			dma_free_coherent(&adapter->pdev->dev,
				STATUS_DESC_RINGSIZE(sds_ring),
				sds_ring->desc_head,
				sds_ring->phys_addr);
			sds_ring->desc_head = NULL;
		}
	}
}