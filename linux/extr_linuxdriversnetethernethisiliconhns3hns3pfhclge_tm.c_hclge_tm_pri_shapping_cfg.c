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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct hclge_pri_shapping_cmd {int /*<<< orphan*/  pri_shapping_para; int /*<<< orphan*/  pri_id; } ;
struct hclge_dev {int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
typedef  enum hclge_shap_bucket { ____Placeholder_hclge_shap_bucket } hclge_shap_bucket ;
typedef  enum hclge_opcode_type { ____Placeholder_hclge_opcode_type } hclge_opcode_type ;

/* Variables and functions */
 int /*<<< orphan*/  BS_B ; 
 int /*<<< orphan*/  BS_S ; 
 int HCLGE_OPC_TM_PRI_C_SHAPPING ; 
 int HCLGE_OPC_TM_PRI_P_SHAPPING ; 
 int /*<<< orphan*/  IR_B ; 
 int /*<<< orphan*/  IR_S ; 
 int /*<<< orphan*/  IR_U ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int,int) ; 
 int /*<<< orphan*/  hclge_tm_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_tm_pri_shapping_cfg(struct hclge_dev *hdev,
				     enum hclge_shap_bucket bucket, u8 pri_id,
				     u8 ir_b, u8 ir_u, u8 ir_s,
				     u8 bs_b, u8 bs_s)
{
	struct hclge_pri_shapping_cmd *shap_cfg_cmd;
	enum hclge_opcode_type opcode;
	struct hclge_desc desc;
	u32 shapping_para = 0;

	opcode = bucket ? HCLGE_OPC_TM_PRI_P_SHAPPING :
		HCLGE_OPC_TM_PRI_C_SHAPPING;

	hclge_cmd_setup_basic_desc(&desc, opcode, false);

	shap_cfg_cmd = (struct hclge_pri_shapping_cmd *)desc.data;

	shap_cfg_cmd->pri_id = pri_id;

	hclge_tm_set_field(shapping_para, IR_B, ir_b);
	hclge_tm_set_field(shapping_para, IR_U, ir_u);
	hclge_tm_set_field(shapping_para, IR_S, ir_s);
	hclge_tm_set_field(shapping_para, BS_B, bs_b);
	hclge_tm_set_field(shapping_para, BS_S, bs_s);

	shap_cfg_cmd->pri_shapping_para = cpu_to_le32(shapping_para);

	return hclge_cmd_send(&hdev->hw, &desc, 1);
}