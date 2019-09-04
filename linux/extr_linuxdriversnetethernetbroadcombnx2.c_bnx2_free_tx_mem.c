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
struct bnx2_tx_ring_info {int /*<<< orphan*/ * tx_buf_ring; int /*<<< orphan*/ * tx_desc_ring; int /*<<< orphan*/  tx_desc_mapping; } ;
struct bnx2_napi {struct bnx2_tx_ring_info tx_ring; } ;
struct bnx2 {int num_tx_rings; TYPE_1__* pdev; struct bnx2_napi* bnx2_napi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TXBD_RING_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bnx2_free_tx_mem(struct bnx2 *bp)
{
	int i;

	for (i = 0; i < bp->num_tx_rings; i++) {
		struct bnx2_napi *bnapi = &bp->bnx2_napi[i];
		struct bnx2_tx_ring_info *txr = &bnapi->tx_ring;

		if (txr->tx_desc_ring) {
			dma_free_coherent(&bp->pdev->dev, TXBD_RING_SIZE,
					  txr->tx_desc_ring,
					  txr->tx_desc_mapping);
			txr->tx_desc_ring = NULL;
		}
		kfree(txr->tx_buf_ring);
		txr->tx_buf_ring = NULL;
	}
}