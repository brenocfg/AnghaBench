#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct il_queue {scalar_t__ n_bd; scalar_t__ read_ptr; scalar_t__ write_ptr; int n_win; } ;
struct il_tx_queue {TYPE_1__* meta; struct il_queue q; } ;
struct il_priv {size_t cmd_queue; int /*<<< orphan*/  pci_dev; struct il_tx_queue* txq; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int CMD_MAPPED ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  dma_unmap_addr (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int il_get_cmd_idx (struct il_queue*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ il_queue_inc_wrap (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  len ; 
 int /*<<< orphan*/  mapping ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
il_cmd_queue_unmap(struct il_priv *il)
{
	struct il_tx_queue *txq = &il->txq[il->cmd_queue];
	struct il_queue *q = &txq->q;
	int i;

	if (q->n_bd == 0)
		return;

	while (q->read_ptr != q->write_ptr) {
		i = il_get_cmd_idx(q, q->read_ptr, 0);

		if (txq->meta[i].flags & CMD_MAPPED) {
			pci_unmap_single(il->pci_dev,
					 dma_unmap_addr(&txq->meta[i], mapping),
					 dma_unmap_len(&txq->meta[i], len),
					 PCI_DMA_BIDIRECTIONAL);
			txq->meta[i].flags = 0;
		}

		q->read_ptr = il_queue_inc_wrap(q->read_ptr, q->n_bd);
	}

	i = q->n_win;
	if (txq->meta[i].flags & CMD_MAPPED) {
		pci_unmap_single(il->pci_dev,
				 dma_unmap_addr(&txq->meta[i], mapping),
				 dma_unmap_len(&txq->meta[i], len),
				 PCI_DMA_BIDIRECTIONAL);
		txq->meta[i].flags = 0;
	}
}