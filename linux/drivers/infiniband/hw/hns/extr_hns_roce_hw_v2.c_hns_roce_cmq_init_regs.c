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
typedef  int u32 ;
struct hns_roce_v2_cmq_ring {int desc_num; scalar_t__ desc_dma_addr; } ;
struct TYPE_2__ {struct hns_roce_v2_cmq_ring crq; struct hns_roce_v2_cmq_ring csq; } ;
struct hns_roce_v2_priv {TYPE_1__ cmq; } ;
struct hns_roce_dev {scalar_t__ priv; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int HNS_ROCE_CMQ_DESC_NUM_S ; 
 int /*<<< orphan*/  ROCEE_RX_CMQ_BASEADDR_H_REG ; 
 int /*<<< orphan*/  ROCEE_RX_CMQ_BASEADDR_L_REG ; 
 int /*<<< orphan*/  ROCEE_RX_CMQ_DEPTH_REG ; 
 int /*<<< orphan*/  ROCEE_RX_CMQ_HEAD_REG ; 
 int /*<<< orphan*/  ROCEE_RX_CMQ_TAIL_REG ; 
 int /*<<< orphan*/  ROCEE_TX_CMQ_BASEADDR_H_REG ; 
 int /*<<< orphan*/  ROCEE_TX_CMQ_BASEADDR_L_REG ; 
 int /*<<< orphan*/  ROCEE_TX_CMQ_DEPTH_REG ; 
 int /*<<< orphan*/  ROCEE_TX_CMQ_HEAD_REG ; 
 int /*<<< orphan*/  ROCEE_TX_CMQ_TAIL_REG ; 
 int TYPE_CSQ ; 
 int /*<<< orphan*/  roce_write (struct hns_roce_dev*,int /*<<< orphan*/ ,int) ; 
 int upper_32_bits (scalar_t__) ; 

__attribute__((used)) static void hns_roce_cmq_init_regs(struct hns_roce_dev *hr_dev, bool ring_type)
{
	struct hns_roce_v2_priv *priv = (struct hns_roce_v2_priv *)hr_dev->priv;
	struct hns_roce_v2_cmq_ring *ring = (ring_type == TYPE_CSQ) ?
					    &priv->cmq.csq : &priv->cmq.crq;
	dma_addr_t dma = ring->desc_dma_addr;

	if (ring_type == TYPE_CSQ) {
		roce_write(hr_dev, ROCEE_TX_CMQ_BASEADDR_L_REG, (u32)dma);
		roce_write(hr_dev, ROCEE_TX_CMQ_BASEADDR_H_REG,
			   upper_32_bits(dma));
		roce_write(hr_dev, ROCEE_TX_CMQ_DEPTH_REG,
			   ring->desc_num >> HNS_ROCE_CMQ_DESC_NUM_S);
		roce_write(hr_dev, ROCEE_TX_CMQ_HEAD_REG, 0);
		roce_write(hr_dev, ROCEE_TX_CMQ_TAIL_REG, 0);
	} else {
		roce_write(hr_dev, ROCEE_RX_CMQ_BASEADDR_L_REG, (u32)dma);
		roce_write(hr_dev, ROCEE_RX_CMQ_BASEADDR_H_REG,
			   upper_32_bits(dma));
		roce_write(hr_dev, ROCEE_RX_CMQ_DEPTH_REG,
			   ring->desc_num >> HNS_ROCE_CMQ_DESC_NUM_S);
		roce_write(hr_dev, ROCEE_RX_CMQ_HEAD_REG, 0);
		roce_write(hr_dev, ROCEE_RX_CMQ_TAIL_REG, 0);
	}
}