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
typedef  int /*<<< orphan*/  tqp_intr_reg_addr_list ;
struct hnae3_handle {int dummy; } ;
struct hclgevf_dev {int num_tqps; int num_msi_used; } ;
typedef  int /*<<< orphan*/  ring_reg_addr_list ;
typedef  int /*<<< orphan*/  common_reg_addr_list ;
typedef  int /*<<< orphan*/  cmdq_reg_addr_list ;

/* Variables and functions */
 int REG_LEN_PER_LINE ; 
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 

__attribute__((used)) static int hclgevf_get_regs_len(struct hnae3_handle *handle)
{
	int cmdq_lines, common_lines, ring_lines, tqp_intr_lines;
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);

	cmdq_lines = sizeof(cmdq_reg_addr_list) / REG_LEN_PER_LINE + 1;
	common_lines = sizeof(common_reg_addr_list) / REG_LEN_PER_LINE + 1;
	ring_lines = sizeof(ring_reg_addr_list) / REG_LEN_PER_LINE + 1;
	tqp_intr_lines = sizeof(tqp_intr_reg_addr_list) / REG_LEN_PER_LINE + 1;

	return (cmdq_lines + common_lines + ring_lines * hdev->num_tqps +
		tqp_intr_lines * (hdev->num_msi_used - 1)) * REG_LEN_PER_LINE;
}