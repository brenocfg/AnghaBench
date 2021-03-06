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
struct hclge_hw {int dummy; } ;

/* Variables and functions */
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
 int /*<<< orphan*/  hclge_write_dev (struct hclge_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hclge_cmd_uninit_regs(struct hclge_hw *hw)
{
	hclge_write_dev(hw, HCLGE_NIC_CSQ_BASEADDR_L_REG, 0);
	hclge_write_dev(hw, HCLGE_NIC_CSQ_BASEADDR_H_REG, 0);
	hclge_write_dev(hw, HCLGE_NIC_CSQ_DEPTH_REG, 0);
	hclge_write_dev(hw, HCLGE_NIC_CSQ_HEAD_REG, 0);
	hclge_write_dev(hw, HCLGE_NIC_CSQ_TAIL_REG, 0);
	hclge_write_dev(hw, HCLGE_NIC_CRQ_BASEADDR_L_REG, 0);
	hclge_write_dev(hw, HCLGE_NIC_CRQ_BASEADDR_H_REG, 0);
	hclge_write_dev(hw, HCLGE_NIC_CRQ_DEPTH_REG, 0);
	hclge_write_dev(hw, HCLGE_NIC_CRQ_HEAD_REG, 0);
	hclge_write_dev(hw, HCLGE_NIC_CRQ_TAIL_REG, 0);
}