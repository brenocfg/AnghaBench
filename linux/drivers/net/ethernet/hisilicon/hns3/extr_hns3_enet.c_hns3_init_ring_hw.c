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
typedef  int u32 ;
struct hns3_enet_ring {int desc_dma_addr; int desc_num; int /*<<< orphan*/  buf_size; struct hnae3_queue* tqp; } ;
struct hnae3_queue {int dummy; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  HNAE3_IS_TX_RING (struct hns3_enet_ring*) ; 
 int /*<<< orphan*/  HNS3_RING_RX_RING_BASEADDR_H_REG ; 
 int /*<<< orphan*/  HNS3_RING_RX_RING_BASEADDR_L_REG ; 
 int /*<<< orphan*/  HNS3_RING_RX_RING_BD_LEN_REG ; 
 int /*<<< orphan*/  HNS3_RING_RX_RING_BD_NUM_REG ; 
 int /*<<< orphan*/  HNS3_RING_TX_RING_BASEADDR_H_REG ; 
 int /*<<< orphan*/  HNS3_RING_TX_RING_BASEADDR_L_REG ; 
 int /*<<< orphan*/  HNS3_RING_TX_RING_BD_NUM_REG ; 
 int hns3_buf_size2type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns3_write_dev (struct hnae3_queue*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hns3_init_ring_hw(struct hns3_enet_ring *ring)
{
	dma_addr_t dma = ring->desc_dma_addr;
	struct hnae3_queue *q = ring->tqp;

	if (!HNAE3_IS_TX_RING(ring)) {
		hns3_write_dev(q, HNS3_RING_RX_RING_BASEADDR_L_REG, (u32)dma);
		hns3_write_dev(q, HNS3_RING_RX_RING_BASEADDR_H_REG,
			       (u32)((dma >> 31) >> 1));

		hns3_write_dev(q, HNS3_RING_RX_RING_BD_LEN_REG,
			       hns3_buf_size2type(ring->buf_size));
		hns3_write_dev(q, HNS3_RING_RX_RING_BD_NUM_REG,
			       ring->desc_num / 8 - 1);

	} else {
		hns3_write_dev(q, HNS3_RING_TX_RING_BASEADDR_L_REG,
			       (u32)dma);
		hns3_write_dev(q, HNS3_RING_TX_RING_BASEADDR_H_REG,
			       (u32)((dma >> 31) >> 1));

		hns3_write_dev(q, HNS3_RING_TX_RING_BD_NUM_REG,
			       ring->desc_num / 8 - 1);
	}
}