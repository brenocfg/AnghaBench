#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct hnae3_knic_private_info {size_t num_tc; } ;
struct TYPE_6__ {struct hnae3_knic_private_info kinfo; } ;
struct hclge_vport {struct hclge_dev* back; TYPE_3__ nic; } ;
struct TYPE_5__ {TYPE_1__* tc_info; } ;
struct hclge_dev {TYPE_2__ tm_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  bw_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_SHAPER_LVL_QSET ; 
 int hclge_shaper_para_calc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hclge_tm_pri_vnet_base_shaper_qs_cfg(struct hclge_vport *vport)
{
	struct hnae3_knic_private_info *kinfo = &vport->nic.kinfo;
	struct hclge_dev *hdev = vport->back;
	u8 ir_u, ir_b, ir_s;
	u32 i;
	int ret;

	for (i = 0; i < kinfo->num_tc; i++) {
		ret = hclge_shaper_para_calc(
					hdev->tm_info.tc_info[i].bw_limit,
					HCLGE_SHAPER_LVL_QSET,
					&ir_b, &ir_u, &ir_s);
		if (ret)
			return ret;
	}

	return 0;
}