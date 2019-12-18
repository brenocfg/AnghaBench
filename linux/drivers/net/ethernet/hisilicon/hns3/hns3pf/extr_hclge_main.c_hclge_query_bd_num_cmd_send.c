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
struct hclge_dev {int /*<<< orphan*/  hw; } ;
struct hclge_desc {int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_CMD_FLAG_NEXT ; 
 int /*<<< orphan*/  HCLGE_OPC_DFX_BD_NUM ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 

int hclge_query_bd_num_cmd_send(struct hclge_dev *hdev, struct hclge_desc *desc)
{
	/*prepare 4 commands to query DFX BD number*/
	hclge_cmd_setup_basic_desc(&desc[0], HCLGE_OPC_DFX_BD_NUM, true);
	desc[0].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
	hclge_cmd_setup_basic_desc(&desc[1], HCLGE_OPC_DFX_BD_NUM, true);
	desc[1].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
	hclge_cmd_setup_basic_desc(&desc[2], HCLGE_OPC_DFX_BD_NUM, true);
	desc[2].flag |= cpu_to_le16(HCLGE_CMD_FLAG_NEXT);
	hclge_cmd_setup_basic_desc(&desc[3], HCLGE_OPC_DFX_BD_NUM, true);

	return hclge_cmd_send(&hdev->hw, desc, 4);
}