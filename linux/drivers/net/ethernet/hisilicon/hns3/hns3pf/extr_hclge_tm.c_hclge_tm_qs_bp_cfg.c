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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct hclge_dev {int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
struct hclge_bp_to_qs_map_cmd {int /*<<< orphan*/  qs_bit_map; void* qs_group_id; void* tc_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_OPC_TM_BP_TO_QSET_MAPPING ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclge_tm_qs_bp_cfg(struct hclge_dev *hdev, u8 tc, u8 grp_id,
			      u32 bit_map)
{
	struct hclge_bp_to_qs_map_cmd *bp_to_qs_map_cmd;
	struct hclge_desc desc;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TM_BP_TO_QSET_MAPPING,
				   false);

	bp_to_qs_map_cmd = (struct hclge_bp_to_qs_map_cmd *)desc.data;

	bp_to_qs_map_cmd->tc_id = tc;
	bp_to_qs_map_cmd->qs_group_id = grp_id;
	bp_to_qs_map_cmd->qs_bit_map = cpu_to_le32(bit_map);

	return hclge_cmd_send(&hdev->hw, &desc, 1);
}