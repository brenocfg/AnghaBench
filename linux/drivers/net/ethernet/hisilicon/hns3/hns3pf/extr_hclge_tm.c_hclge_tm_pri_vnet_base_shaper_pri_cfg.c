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
struct hclge_vport {int /*<<< orphan*/  vport_id; int /*<<< orphan*/  bw_limit; struct hclge_dev* back; } ;
struct hclge_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_SHAPER_BS_S_DEF ; 
 int /*<<< orphan*/  HCLGE_SHAPER_BS_U_DEF ; 
 int /*<<< orphan*/  HCLGE_SHAPER_LVL_VF ; 
 int /*<<< orphan*/  HCLGE_TM_SHAP_C_BUCKET ; 
 int /*<<< orphan*/  HCLGE_TM_SHAP_P_BUCKET ; 
 int hclge_shaper_para_calc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hclge_tm_get_shapping_para (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hclge_tm_pri_shapping_cfg (struct hclge_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_tm_pri_vnet_base_shaper_pri_cfg(struct hclge_vport *vport)
{
	struct hclge_dev *hdev = vport->back;
	u8 ir_u, ir_b, ir_s;
	u32 shaper_para;
	int ret;

	ret = hclge_shaper_para_calc(vport->bw_limit, HCLGE_SHAPER_LVL_VF,
				     &ir_b, &ir_u, &ir_s);
	if (ret)
		return ret;

	shaper_para = hclge_tm_get_shapping_para(0, 0, 0,
						 HCLGE_SHAPER_BS_U_DEF,
						 HCLGE_SHAPER_BS_S_DEF);
	ret = hclge_tm_pri_shapping_cfg(hdev, HCLGE_TM_SHAP_C_BUCKET,
					vport->vport_id, shaper_para);
	if (ret)
		return ret;

	shaper_para = hclge_tm_get_shapping_para(ir_b, ir_u, ir_s,
						 HCLGE_SHAPER_BS_U_DEF,
						 HCLGE_SHAPER_BS_S_DEF);
	ret = hclge_tm_pri_shapping_cfg(hdev, HCLGE_TM_SHAP_P_BUCKET,
					vport->vport_id, shaper_para);
	if (ret)
		return ret;

	return 0;
}