#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int count; int size; scalar_t__ consume_idx; scalar_t__ produce_idx; scalar_t__ v_addr; scalar_t__ dma_addr; int /*<<< orphan*/  tpbuff; } ;
struct emac_tx_queue {TYPE_3__ tpd; } ;
struct emac_ring_header {scalar_t__ used; scalar_t__ v_addr; scalar_t__ dma_addr; } ;
struct emac_buffer {int dummy; } ;
struct emac_adapter {int tpd_size; TYPE_2__* netdev; struct emac_ring_header ring_header; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ ALIGN (int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int dev_to_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc_node (size_t,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int emac_tx_q_desc_alloc(struct emac_adapter *adpt,
				struct emac_tx_queue *tx_q)
{
	struct emac_ring_header *ring_header = &adpt->ring_header;
	int node = dev_to_node(adpt->netdev->dev.parent);
	size_t size;

	size = sizeof(struct emac_buffer) * tx_q->tpd.count;
	tx_q->tpd.tpbuff = kzalloc_node(size, GFP_KERNEL, node);
	if (!tx_q->tpd.tpbuff)
		return -ENOMEM;

	tx_q->tpd.size = tx_q->tpd.count * (adpt->tpd_size * 4);
	tx_q->tpd.dma_addr = ring_header->dma_addr + ring_header->used;
	tx_q->tpd.v_addr = ring_header->v_addr + ring_header->used;
	ring_header->used += ALIGN(tx_q->tpd.size, 8);
	tx_q->tpd.produce_idx = 0;
	tx_q->tpd.consume_idx = 0;

	return 0;
}