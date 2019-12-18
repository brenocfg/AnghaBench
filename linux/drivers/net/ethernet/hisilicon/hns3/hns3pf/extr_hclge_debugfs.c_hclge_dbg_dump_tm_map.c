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
struct hclge_tqp_tx_queue_tc_cmd {int tc_id; void* queue_id; } ;
struct hclge_qs_to_pri_link_cmd {int priority; void* qs_id; } ;
struct hclge_nq_to_qs_link_cmd {int qset_id; void* nq_id; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
struct hclge_bp_to_qs_map_cmd {int tc_id; int qs_group_id; int qs_bit_map; } ;
typedef  enum hclge_opcode_type { ____Placeholder_hclge_opcode_type } hclge_opcode_type ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HCLGE_OPC_TM_BP_TO_QSET_MAPPING ; 
 int HCLGE_OPC_TM_NQ_TO_QS_LINK ; 
 int HCLGE_OPC_TM_QS_TO_PRI_LINK ; 
 int HCLGE_OPC_TQP_TX_QUEUE_TC ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int,int) ; 
 int /*<<< orphan*/  hnae3_dev_dcb_supported (struct hclge_dev*) ; 
 int kstrtouint (char const*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void hclge_dbg_dump_tm_map(struct hclge_dev *hdev,
				  const char *cmd_buf)
{
	struct hclge_bp_to_qs_map_cmd *bp_to_qs_map_cmd;
	struct hclge_nq_to_qs_link_cmd *nq_to_qs_map;
	struct hclge_qs_to_pri_link_cmd *map;
	struct hclge_tqp_tx_queue_tc_cmd *tc;
	enum hclge_opcode_type cmd;
	struct hclge_desc desc;
	int queue_id, group_id;
	u32 qset_maping[32];
	int tc_id, qset_id;
	int pri_id, ret;
	u32 i;

	ret = kstrtouint(cmd_buf, 0, &queue_id);
	queue_id = (ret != 0) ? 0 : queue_id;

	cmd = HCLGE_OPC_TM_NQ_TO_QS_LINK;
	nq_to_qs_map = (struct hclge_nq_to_qs_link_cmd *)desc.data;
	hclge_cmd_setup_basic_desc(&desc, cmd, true);
	nq_to_qs_map->nq_id = cpu_to_le16(queue_id);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret)
		goto err_tm_map_cmd_send;
	qset_id = nq_to_qs_map->qset_id & 0x3FF;

	cmd = HCLGE_OPC_TM_QS_TO_PRI_LINK;
	map = (struct hclge_qs_to_pri_link_cmd *)desc.data;
	hclge_cmd_setup_basic_desc(&desc, cmd, true);
	map->qs_id = cpu_to_le16(qset_id);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret)
		goto err_tm_map_cmd_send;
	pri_id = map->priority;

	cmd = HCLGE_OPC_TQP_TX_QUEUE_TC;
	tc = (struct hclge_tqp_tx_queue_tc_cmd *)desc.data;
	hclge_cmd_setup_basic_desc(&desc, cmd, true);
	tc->queue_id = cpu_to_le16(queue_id);
	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret)
		goto err_tm_map_cmd_send;
	tc_id = tc->tc_id & 0x7;

	dev_info(&hdev->pdev->dev, "queue_id | qset_id | pri_id | tc_id\n");
	dev_info(&hdev->pdev->dev, "%04d     | %04d    | %02d     | %02d\n",
		 queue_id, qset_id, pri_id, tc_id);

	if (!hnae3_dev_dcb_supported(hdev)) {
		dev_info(&hdev->pdev->dev,
			 "Only DCB-supported dev supports tm mapping\n");
		return;
	}

	cmd = HCLGE_OPC_TM_BP_TO_QSET_MAPPING;
	bp_to_qs_map_cmd = (struct hclge_bp_to_qs_map_cmd *)desc.data;
	for (group_id = 0; group_id < 32; group_id++) {
		hclge_cmd_setup_basic_desc(&desc, cmd, true);
		bp_to_qs_map_cmd->tc_id = tc_id;
		bp_to_qs_map_cmd->qs_group_id = group_id;
		ret = hclge_cmd_send(&hdev->hw, &desc, 1);
		if (ret)
			goto err_tm_map_cmd_send;

		qset_maping[group_id] = bp_to_qs_map_cmd->qs_bit_map;
	}

	dev_info(&hdev->pdev->dev, "index | tm bp qset maping:\n");

	i = 0;
	for (group_id = 0; group_id < 4; group_id++) {
		dev_info(&hdev->pdev->dev,
			 "%04d  | %08x:%08x:%08x:%08x:%08x:%08x:%08x:%08x\n",
			 group_id * 256, qset_maping[(u32)(i + 7)],
			 qset_maping[(u32)(i + 6)], qset_maping[(u32)(i + 5)],
			 qset_maping[(u32)(i + 4)], qset_maping[(u32)(i + 3)],
			 qset_maping[(u32)(i + 2)], qset_maping[(u32)(i + 1)],
			 qset_maping[i]);
		i += 8;
	}

	return;

err_tm_map_cmd_send:
	dev_err(&hdev->pdev->dev, "dump tqp map fail(0x%x), ret = %d\n",
		cmd, ret);
}