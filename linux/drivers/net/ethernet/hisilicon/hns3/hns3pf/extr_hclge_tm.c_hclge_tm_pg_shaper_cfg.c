#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct TYPE_4__ {size_t num_pg; TYPE_1__* pg_info; } ;
struct hclge_dev {scalar_t__ tx_sch_mode; TYPE_2__ tm_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  bw_limit; } ;

/* Variables and functions */
 scalar_t__ HCLGE_FLAG_TC_BASE_SCH_MODE ; 
 int /*<<< orphan*/  HCLGE_SHAPER_BS_S_DEF ; 
 int /*<<< orphan*/  HCLGE_SHAPER_BS_U_DEF ; 
 int /*<<< orphan*/  HCLGE_SHAPER_LVL_PG ; 
 int /*<<< orphan*/  HCLGE_TM_SHAP_C_BUCKET ; 
 int /*<<< orphan*/  HCLGE_TM_SHAP_P_BUCKET ; 
 int hclge_shaper_para_calc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t hclge_tm_get_shapping_para (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hclge_tm_pg_shapping_cfg (struct hclge_dev*,int /*<<< orphan*/ ,size_t,size_t) ; 

__attribute__((used)) static int hclge_tm_pg_shaper_cfg(struct hclge_dev *hdev)
{
	u8 ir_u, ir_b, ir_s;
	u32 shaper_para;
	int ret;
	u32 i;

	/* Cfg pg schd */
	if (hdev->tx_sch_mode != HCLGE_FLAG_TC_BASE_SCH_MODE)
		return 0;

	/* Pg to pri */
	for (i = 0; i < hdev->tm_info.num_pg; i++) {
		/* Calc shaper para */
		ret = hclge_shaper_para_calc(
					hdev->tm_info.pg_info[i].bw_limit,
					HCLGE_SHAPER_LVL_PG,
					&ir_b, &ir_u, &ir_s);
		if (ret)
			return ret;

		shaper_para = hclge_tm_get_shapping_para(0, 0, 0,
							 HCLGE_SHAPER_BS_U_DEF,
							 HCLGE_SHAPER_BS_S_DEF);
		ret = hclge_tm_pg_shapping_cfg(hdev,
					       HCLGE_TM_SHAP_C_BUCKET, i,
					       shaper_para);
		if (ret)
			return ret;

		shaper_para = hclge_tm_get_shapping_para(ir_b, ir_u, ir_s,
							 HCLGE_SHAPER_BS_U_DEF,
							 HCLGE_SHAPER_BS_S_DEF);
		ret = hclge_tm_pg_shapping_cfg(hdev,
					       HCLGE_TM_SHAP_P_BUCKET, i,
					       shaper_para);
		if (ret)
			return ret;
	}

	return 0;
}