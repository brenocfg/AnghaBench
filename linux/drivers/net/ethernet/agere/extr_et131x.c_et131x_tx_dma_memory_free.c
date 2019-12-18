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
struct tx_ring {int /*<<< orphan*/  tcb_ring; int /*<<< orphan*/ * tx_status; int /*<<< orphan*/  tx_status_pa; int /*<<< orphan*/ * tx_desc_ring; int /*<<< orphan*/  tx_desc_ring_pa; } ;
struct tx_desc {int dummy; } ;
struct et131x_adapter {TYPE_1__* pdev; struct tx_ring tx_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int NUM_DESC_PER_RING_TX ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void et131x_tx_dma_memory_free(struct et131x_adapter *adapter)
{
	int desc_size = 0;
	struct tx_ring *tx_ring = &adapter->tx_ring;

	if (tx_ring->tx_desc_ring) {
		/* Free memory relating to Tx rings here */
		desc_size = (sizeof(struct tx_desc) * NUM_DESC_PER_RING_TX);
		dma_free_coherent(&adapter->pdev->dev,
				  desc_size,
				  tx_ring->tx_desc_ring,
				  tx_ring->tx_desc_ring_pa);
		tx_ring->tx_desc_ring = NULL;
	}

	/* Free memory for the Tx status block */
	if (tx_ring->tx_status) {
		dma_free_coherent(&adapter->pdev->dev,
				  sizeof(u32),
				  tx_ring->tx_status,
				  tx_ring->tx_status_pa);

		tx_ring->tx_status = NULL;
	}
	/* Free the memory for the tcb structures */
	kfree(tx_ring->tcb_ring);
}