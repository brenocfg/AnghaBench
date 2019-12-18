#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int count; int size; scalar_t__ consume_idx; scalar_t__ produce_idx; scalar_t__ v_addr; scalar_t__ dma_addr; int /*<<< orphan*/  rfbuff; } ;
struct TYPE_7__ {int size; int count; scalar_t__ consume_idx; scalar_t__ produce_idx; scalar_t__ v_addr; scalar_t__ dma_addr; } ;
struct emac_rx_queue {TYPE_4__ rfd; TYPE_3__ rrd; } ;
struct emac_ring_header {scalar_t__ used; scalar_t__ v_addr; scalar_t__ dma_addr; } ;
struct emac_buffer {int dummy; } ;
struct emac_adapter {int rrd_size; int rfd_size; struct emac_rx_queue rx_q; TYPE_2__* netdev; struct emac_ring_header ring_header; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct TYPE_6__ {TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ ALIGN (int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int dev_to_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc_node (size_t,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int emac_rx_descs_alloc(struct emac_adapter *adpt)
{
	struct emac_ring_header *ring_header = &adpt->ring_header;
	int node = dev_to_node(adpt->netdev->dev.parent);
	struct emac_rx_queue *rx_q = &adpt->rx_q;
	size_t size;

	size = sizeof(struct emac_buffer) * rx_q->rfd.count;
	rx_q->rfd.rfbuff = kzalloc_node(size, GFP_KERNEL, node);
	if (!rx_q->rfd.rfbuff)
		return -ENOMEM;

	rx_q->rrd.size = rx_q->rrd.count * (adpt->rrd_size * 4);
	rx_q->rfd.size = rx_q->rfd.count * (adpt->rfd_size * 4);

	rx_q->rrd.dma_addr = ring_header->dma_addr + ring_header->used;
	rx_q->rrd.v_addr   = ring_header->v_addr + ring_header->used;
	ring_header->used += ALIGN(rx_q->rrd.size, 8);

	rx_q->rfd.dma_addr = ring_header->dma_addr + ring_header->used;
	rx_q->rfd.v_addr   = ring_header->v_addr + ring_header->used;
	ring_header->used += ALIGN(rx_q->rfd.size, 8);

	rx_q->rrd.produce_idx = 0;
	rx_q->rrd.consume_idx = 0;

	rx_q->rfd.produce_idx = 0;
	rx_q->rfd.consume_idx = 0;

	return 0;
}