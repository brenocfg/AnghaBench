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
typedef  size_t u8 ;
struct TYPE_4__ {TYPE_1__* tc_info; } ;
struct hclge_dev {int /*<<< orphan*/  hw; TYPE_2__ tm_info; } ;
struct hclge_desc {void** data; } ;
struct TYPE_3__ {scalar_t__ tc_sch_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_OPC_TM_PRI_SCH_MODE_CFG ; 
 scalar_t__ HCLGE_SCH_MODE_DWRR ; 
 size_t HCLGE_TM_TX_SCHD_DWRR_MSK ; 
 void* cpu_to_le32 (size_t) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclge_tm_pri_schd_mode_cfg(struct hclge_dev *hdev, u8 pri_id)
{
	struct hclge_desc desc;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_TM_PRI_SCH_MODE_CFG, false);

	if (hdev->tm_info.tc_info[pri_id].tc_sch_mode == HCLGE_SCH_MODE_DWRR)
		desc.data[1] = cpu_to_le32(HCLGE_TM_TX_SCHD_DWRR_MSK);
	else
		desc.data[1] = 0;

	desc.data[0] = cpu_to_le32(pri_id);

	return hclge_cmd_send(&hdev->hw, &desc, 1);
}