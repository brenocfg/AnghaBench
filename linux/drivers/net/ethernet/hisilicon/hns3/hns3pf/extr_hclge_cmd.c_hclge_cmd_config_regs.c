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
struct hclge_hw {int dummy; } ;
struct hclge_dev {struct hclge_hw hw; } ;
struct hclge_cmq_ring {scalar_t__ ring_type; int desc_num; struct hclge_dev* dev; int /*<<< orphan*/  desc_dma_addr; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int HCLGE_NIC_CMQ_DESC_NUM_S ; 
 int /*<<< orphan*/  HCLGE_NIC_CRQ_BASEADDR_H_REG ; 
 int /*<<< orphan*/  HCLGE_NIC_CRQ_BASEADDR_L_REG ; 
 int /*<<< orphan*/  HCLGE_NIC_CRQ_DEPTH_REG ; 
 int /*<<< orphan*/  HCLGE_NIC_CRQ_HEAD_REG ; 
 int /*<<< orphan*/  HCLGE_NIC_CRQ_TAIL_REG ; 
 int /*<<< orphan*/  HCLGE_NIC_CSQ_BASEADDR_H_REG ; 
 int /*<<< orphan*/  HCLGE_NIC_CSQ_BASEADDR_L_REG ; 
 int /*<<< orphan*/  HCLGE_NIC_CSQ_DEPTH_REG ; 
 int /*<<< orphan*/  HCLGE_NIC_CSQ_HEAD_REG ; 
 int /*<<< orphan*/  HCLGE_NIC_CSQ_TAIL_REG ; 
 int HCLGE_NIC_SW_RST_RDY ; 
 scalar_t__ HCLGE_TYPE_CSQ ; 
 int hclge_read_dev (struct hclge_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclge_write_dev (struct hclge_hw*,int /*<<< orphan*/ ,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hclge_cmd_config_regs(struct hclge_cmq_ring *ring)
{
	dma_addr_t dma = ring->desc_dma_addr;
	struct hclge_dev *hdev = ring->dev;
	struct hclge_hw *hw = &hdev->hw;
	u32 reg_val;

	if (ring->ring_type == HCLGE_TYPE_CSQ) {
		hclge_write_dev(hw, HCLGE_NIC_CSQ_BASEADDR_L_REG,
				lower_32_bits(dma));
		hclge_write_dev(hw, HCLGE_NIC_CSQ_BASEADDR_H_REG,
				upper_32_bits(dma));
		reg_val = hclge_read_dev(hw, HCLGE_NIC_CSQ_DEPTH_REG);
		reg_val &= HCLGE_NIC_SW_RST_RDY;
		reg_val |= ring->desc_num >> HCLGE_NIC_CMQ_DESC_NUM_S;
		hclge_write_dev(hw, HCLGE_NIC_CSQ_DEPTH_REG, reg_val);
		hclge_write_dev(hw, HCLGE_NIC_CSQ_HEAD_REG, 0);
		hclge_write_dev(hw, HCLGE_NIC_CSQ_TAIL_REG, 0);
	} else {
		hclge_write_dev(hw, HCLGE_NIC_CRQ_BASEADDR_L_REG,
				lower_32_bits(dma));
		hclge_write_dev(hw, HCLGE_NIC_CRQ_BASEADDR_H_REG,
				upper_32_bits(dma));
		hclge_write_dev(hw, HCLGE_NIC_CRQ_DEPTH_REG,
				ring->desc_num >> HCLGE_NIC_CMQ_DESC_NUM_S);
		hclge_write_dev(hw, HCLGE_NIC_CRQ_HEAD_REG, 0);
		hclge_write_dev(hw, HCLGE_NIC_CRQ_TAIL_REG, 0);
	}
}