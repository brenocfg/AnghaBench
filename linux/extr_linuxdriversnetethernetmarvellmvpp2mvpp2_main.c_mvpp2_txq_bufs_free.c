#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mvpp2_txq_pcpu_buf {scalar_t__ skb; int /*<<< orphan*/  size; int /*<<< orphan*/  dma; } ;
struct mvpp2_txq_pcpu {int txq_get_index; struct mvpp2_txq_pcpu_buf* buffs; } ;
struct mvpp2_tx_queue {int dummy; } ;
struct mvpp2_port {TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct TYPE_3__ {TYPE_2__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  IS_TSO_HEADER (struct mvpp2_txq_pcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_txq_inc_get (struct mvpp2_txq_pcpu*) ; 

__attribute__((used)) static void mvpp2_txq_bufs_free(struct mvpp2_port *port,
				struct mvpp2_tx_queue *txq,
				struct mvpp2_txq_pcpu *txq_pcpu, int num)
{
	int i;

	for (i = 0; i < num; i++) {
		struct mvpp2_txq_pcpu_buf *tx_buf =
			txq_pcpu->buffs + txq_pcpu->txq_get_index;

		if (!IS_TSO_HEADER(txq_pcpu, tx_buf->dma))
			dma_unmap_single(port->dev->dev.parent, tx_buf->dma,
					 tx_buf->size, DMA_TO_DEVICE);
		if (tx_buf->skb)
			dev_kfree_skb_any(tx_buf->skb);

		mvpp2_txq_inc_get(txq_pcpu);
	}
}