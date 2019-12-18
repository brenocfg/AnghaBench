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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct mvneta_tx_queue {size_t txq_put_index; struct sk_buff** tx_skb; } ;
struct mvneta_tx_desc {int data_size; scalar_t__ command; int /*<<< orphan*/  buf_phys_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 scalar_t__ MVNETA_TXD_L_DESC ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvneta_txq_desc_put (struct mvneta_tx_queue*) ; 
 int /*<<< orphan*/  mvneta_txq_inc_put (struct mvneta_tx_queue*) ; 
 struct mvneta_tx_desc* mvneta_txq_next_desc_get (struct mvneta_tx_queue*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
mvneta_tso_put_data(struct net_device *dev, struct mvneta_tx_queue *txq,
		    struct sk_buff *skb, char *data, int size,
		    bool last_tcp, bool is_last)
{
	struct mvneta_tx_desc *tx_desc;

	tx_desc = mvneta_txq_next_desc_get(txq);
	tx_desc->data_size = size;
	tx_desc->buf_phys_addr = dma_map_single(dev->dev.parent, data,
						size, DMA_TO_DEVICE);
	if (unlikely(dma_mapping_error(dev->dev.parent,
		     tx_desc->buf_phys_addr))) {
		mvneta_txq_desc_put(txq);
		return -ENOMEM;
	}

	tx_desc->command = 0;
	txq->tx_skb[txq->txq_put_index] = NULL;

	if (last_tcp) {
		/* last descriptor in the TCP packet */
		tx_desc->command = MVNETA_TXD_L_DESC;

		/* last descriptor in SKB */
		if (is_last)
			txq->tx_skb[txq->txq_put_index] = skb;
	}
	mvneta_txq_inc_put(txq);
	return 0;
}