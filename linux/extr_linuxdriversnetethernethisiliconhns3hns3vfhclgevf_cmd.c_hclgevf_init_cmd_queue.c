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
struct hclgevf_hw {int dummy; } ;
struct hclgevf_dev {TYPE_1__* pdev; struct hclgevf_hw hw; } ;
struct hclgevf_cmq_ring {int flag; int desc_num; int desc_dma_addr; struct hclgevf_dev* dev; scalar_t__ next_to_use; scalar_t__ next_to_clean; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HCLGEVF_NIC_CMQ_DESC_NUM ; 
 int HCLGEVF_NIC_CMQ_DESC_NUM_S ; 
 int HCLGEVF_NIC_CMQ_ENABLE ; 
 int /*<<< orphan*/  HCLGEVF_NIC_CRQ_BASEADDR_H_REG ; 
 int /*<<< orphan*/  HCLGEVF_NIC_CRQ_BASEADDR_L_REG ; 
 int /*<<< orphan*/  HCLGEVF_NIC_CRQ_DEPTH_REG ; 
 int /*<<< orphan*/  HCLGEVF_NIC_CRQ_HEAD_REG ; 
 int /*<<< orphan*/  HCLGEVF_NIC_CRQ_TAIL_REG ; 
 int /*<<< orphan*/  HCLGEVF_NIC_CSQ_BASEADDR_H_REG ; 
 int /*<<< orphan*/  HCLGEVF_NIC_CSQ_BASEADDR_L_REG ; 
 int /*<<< orphan*/  HCLGEVF_NIC_CSQ_DEPTH_REG ; 
 int /*<<< orphan*/  HCLGEVF_NIC_CSQ_HEAD_REG ; 
 int /*<<< orphan*/  HCLGEVF_NIC_CSQ_TAIL_REG ; 
#define  HCLGEVF_TYPE_CRQ 129 
#define  HCLGEVF_TYPE_CSQ 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,char*) ; 
 int hclgevf_alloc_cmd_desc (struct hclgevf_cmq_ring*) ; 
 int /*<<< orphan*/  hclgevf_write_dev (struct hclgevf_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hclgevf_init_cmd_queue(struct hclgevf_dev *hdev,
				  struct hclgevf_cmq_ring *ring)
{
	struct hclgevf_hw *hw = &hdev->hw;
	int ring_type = ring->flag;
	u32 reg_val;
	int ret;

	ring->desc_num = HCLGEVF_NIC_CMQ_DESC_NUM;
	spin_lock_init(&ring->lock);
	ring->next_to_clean = 0;
	ring->next_to_use = 0;
	ring->dev = hdev;

	/* allocate CSQ/CRQ descriptor */
	ret = hclgevf_alloc_cmd_desc(ring);
	if (ret) {
		dev_err(&hdev->pdev->dev, "failed(%d) to alloc %s desc\n", ret,
			(ring_type == HCLGEVF_TYPE_CSQ) ? "CSQ" : "CRQ");
		return ret;
	}

	/* initialize the hardware registers with csq/crq dma-address,
	 * descriptor number, head & tail pointers
	 */
	switch (ring_type) {
	case HCLGEVF_TYPE_CSQ:
		reg_val = (u32)ring->desc_dma_addr;
		hclgevf_write_dev(hw, HCLGEVF_NIC_CSQ_BASEADDR_L_REG, reg_val);
		reg_val = (u32)((ring->desc_dma_addr >> 31) >> 1);
		hclgevf_write_dev(hw, HCLGEVF_NIC_CSQ_BASEADDR_H_REG, reg_val);

		reg_val = (ring->desc_num >> HCLGEVF_NIC_CMQ_DESC_NUM_S);
		reg_val |= HCLGEVF_NIC_CMQ_ENABLE;
		hclgevf_write_dev(hw, HCLGEVF_NIC_CSQ_DEPTH_REG, reg_val);

		hclgevf_write_dev(hw, HCLGEVF_NIC_CSQ_TAIL_REG, 0);
		hclgevf_write_dev(hw, HCLGEVF_NIC_CSQ_HEAD_REG, 0);
		break;
	case HCLGEVF_TYPE_CRQ:
		reg_val = (u32)ring->desc_dma_addr;
		hclgevf_write_dev(hw, HCLGEVF_NIC_CRQ_BASEADDR_L_REG, reg_val);
		reg_val = (u32)((ring->desc_dma_addr >> 31) >> 1);
		hclgevf_write_dev(hw, HCLGEVF_NIC_CRQ_BASEADDR_H_REG, reg_val);

		reg_val = (ring->desc_num >> HCLGEVF_NIC_CMQ_DESC_NUM_S);
		reg_val |= HCLGEVF_NIC_CMQ_ENABLE;
		hclgevf_write_dev(hw, HCLGEVF_NIC_CRQ_DEPTH_REG, reg_val);

		hclgevf_write_dev(hw, HCLGEVF_NIC_CRQ_TAIL_REG, 0);
		hclgevf_write_dev(hw, HCLGEVF_NIC_CRQ_HEAD_REG, 0);
		break;
	}

	return 0;
}