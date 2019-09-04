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
typedef  scalar_t__ u32 ;
struct hnae_ring {int desc_dma_addr; int /*<<< orphan*/  buf_size; } ;
struct hnae_queue {struct hnae_ring tx_ring; struct hnae_ring rx_ring; } ;
struct ring_pair_cb {scalar_t__ port_id_in_comm; struct hnae_queue q; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 scalar_t__ HNS_RCB_TX_PKTLINE_OFFSET ; 
 int /*<<< orphan*/  RCB_RING_RX_RING_BASEADDR_H_REG ; 
 int /*<<< orphan*/  RCB_RING_RX_RING_BASEADDR_L_REG ; 
 int /*<<< orphan*/  RCB_RING_RX_RING_BD_NUM_REG ; 
 int /*<<< orphan*/  RCB_RING_RX_RING_PKTLINE_REG ; 
 int /*<<< orphan*/  RCB_RING_TX_RING_BASEADDR_H_REG ; 
 int /*<<< orphan*/  RCB_RING_TX_RING_BASEADDR_L_REG ; 
 int /*<<< orphan*/  RCB_RING_TX_RING_BD_NUM_REG ; 
 int /*<<< orphan*/  RCB_RING_TX_RING_PKTLINE_REG ; 
 int RX_RING ; 
 int /*<<< orphan*/  dsaf_write_dev (struct hnae_queue*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hns_rcb_set_rx_ring_bs (struct hnae_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_rcb_set_tx_ring_bs (struct hnae_queue*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_rcb_ring_init(struct ring_pair_cb *ring_pair, int ring_type)
{
	struct hnae_queue *q = &ring_pair->q;
	struct hnae_ring *ring =
		(ring_type == RX_RING) ? &q->rx_ring : &q->tx_ring;
	dma_addr_t dma = ring->desc_dma_addr;

	if (ring_type == RX_RING) {
		dsaf_write_dev(q, RCB_RING_RX_RING_BASEADDR_L_REG,
			       (u32)dma);
		dsaf_write_dev(q, RCB_RING_RX_RING_BASEADDR_H_REG,
			       (u32)((dma >> 31) >> 1));

		hns_rcb_set_rx_ring_bs(q, ring->buf_size);

		dsaf_write_dev(q, RCB_RING_RX_RING_BD_NUM_REG,
			       ring_pair->port_id_in_comm);
		dsaf_write_dev(q, RCB_RING_RX_RING_PKTLINE_REG,
			       ring_pair->port_id_in_comm);
	} else {
		dsaf_write_dev(q, RCB_RING_TX_RING_BASEADDR_L_REG,
			       (u32)dma);
		dsaf_write_dev(q, RCB_RING_TX_RING_BASEADDR_H_REG,
			       (u32)((dma >> 31) >> 1));

		hns_rcb_set_tx_ring_bs(q, ring->buf_size);

		dsaf_write_dev(q, RCB_RING_TX_RING_BD_NUM_REG,
			       ring_pair->port_id_in_comm);
		dsaf_write_dev(q, RCB_RING_TX_RING_PKTLINE_REG,
			ring_pair->port_id_in_comm + HNS_RCB_TX_PKTLINE_OFFSET);
	}
}