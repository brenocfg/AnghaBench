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
struct hclgevf_hw {int dummy; } ;

/* Variables and functions */
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
 int /*<<< orphan*/  hclgevf_write_dev (struct hclgevf_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hclgevf_cmd_uninit_regs(struct hclgevf_hw *hw)
{
	hclgevf_write_dev(hw, HCLGEVF_NIC_CSQ_BASEADDR_L_REG, 0);
	hclgevf_write_dev(hw, HCLGEVF_NIC_CSQ_BASEADDR_H_REG, 0);
	hclgevf_write_dev(hw, HCLGEVF_NIC_CSQ_DEPTH_REG, 0);
	hclgevf_write_dev(hw, HCLGEVF_NIC_CSQ_HEAD_REG, 0);
	hclgevf_write_dev(hw, HCLGEVF_NIC_CSQ_TAIL_REG, 0);
	hclgevf_write_dev(hw, HCLGEVF_NIC_CRQ_BASEADDR_L_REG, 0);
	hclgevf_write_dev(hw, HCLGEVF_NIC_CRQ_BASEADDR_H_REG, 0);
	hclgevf_write_dev(hw, HCLGEVF_NIC_CRQ_DEPTH_REG, 0);
	hclgevf_write_dev(hw, HCLGEVF_NIC_CRQ_HEAD_REG, 0);
	hclgevf_write_dev(hw, HCLGEVF_NIC_CRQ_TAIL_REG, 0);
}