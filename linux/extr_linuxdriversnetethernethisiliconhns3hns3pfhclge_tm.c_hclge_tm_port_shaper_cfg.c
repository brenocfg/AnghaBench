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
struct hclge_port_shapping_cmd {int /*<<< orphan*/  port_shapping_para; } ;
struct hclge_dev {int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BS_B ; 
 int /*<<< orphan*/  BS_S ; 
 int /*<<< orphan*/  HCLGE_ETHER_MAX_RATE ; 
 int /*<<< orphan*/  HCLGE_OPC_TM_PORT_SHAPPING ; 
 int /*<<< orphan*/  HCLGE_SHAPER_BS_S_DEF ; 
 int /*<<< orphan*/  HCLGE_SHAPER_BS_U_DEF ; 
 int /*<<< orphan*/  HCLGE_SHAPER_LVL_PORT ; 
 int /*<<< orphan*/  IR_B ; 
 int /*<<< orphan*/  IR_S ; 
 int /*<<< orphan*/  IR_U ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int hclge_shaper_para_calc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hclge_tm_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_tm_port_shaper_cfg(struct hclge_dev *hdev)
{
	struct hclge_port_shapping_cmd *shap_cfg_cmd;
	struct hclge_desc desc;
	u32 shapping_para = 0;
	u8 ir_u, ir_b, ir_s;
	int ret;

	ret = hclge_shaper_para_calc(HCLGE_ETHER_MAX_RATE,
				     HCLGE_SHAPER_LVL_PORT,
				     &ir_b, &ir_u, &ir_s);
	if (ret)
		return ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TM_PORT_SHAPPING, false);
	shap_cfg_cmd = (struct hclge_port_shapping_cmd *)desc.data;

	hclge_tm_set_field(shapping_para, IR_B, ir_b);
	hclge_tm_set_field(shapping_para, IR_U, ir_u);
	hclge_tm_set_field(shapping_para, IR_S, ir_s);
	hclge_tm_set_field(shapping_para, BS_B, HCLGE_SHAPER_BS_U_DEF);
	hclge_tm_set_field(shapping_para, BS_S, HCLGE_SHAPER_BS_S_DEF);

	shap_cfg_cmd->port_shapping_para = cpu_to_le32(shapping_para);

	return hclge_cmd_send(&hdev->hw, &desc, 1);
}