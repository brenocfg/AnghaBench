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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct bnxt_ring_struct {int /*<<< orphan*/  ring_mem; } ;
struct bnxt_tx_ring_info {struct bnxt_ring_struct tx_ring_struct; int /*<<< orphan*/ * tx_push; int /*<<< orphan*/  tx_push_mapping; } ;
struct bnxt {int tx_nr_rings; int /*<<< orphan*/  tx_push_size; struct bnxt_tx_ring_info* tx_ring; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_free_ring (struct bnxt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_free_tx_rings(struct bnxt *bp)
{
	int i;
	struct pci_dev *pdev = bp->pdev;

	if (!bp->tx_ring)
		return;

	for (i = 0; i < bp->tx_nr_rings; i++) {
		struct bnxt_tx_ring_info *txr = &bp->tx_ring[i];
		struct bnxt_ring_struct *ring;

		if (txr->tx_push) {
			dma_free_coherent(&pdev->dev, bp->tx_push_size,
					  txr->tx_push, txr->tx_push_mapping);
			txr->tx_push = NULL;
		}

		ring = &txr->tx_ring_struct;

		bnxt_free_ring(bp, &ring->ring_mem);
	}
}