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
typedef  size_t u8 ;
struct hnae3_knic_private_info {size_t num_tc; } ;
struct TYPE_6__ {struct hnae3_knic_private_info kinfo; } ;
struct hclge_vport {scalar_t__ qs_offset; int /*<<< orphan*/  vport_id; struct hclge_dev* back; TYPE_3__ nic; } ;
struct TYPE_5__ {TYPE_1__* tc_info; } ;
struct hclge_dev {TYPE_2__ tm_info; } ;
struct TYPE_4__ {size_t tc_sch_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HNAE3_MAX_TC ; 
 int hclge_tm_pri_schd_mode_cfg (struct hclge_dev*,int /*<<< orphan*/ ) ; 
 int hclge_tm_qs_schd_mode_cfg (struct hclge_dev*,scalar_t__,size_t) ; 

__attribute__((used)) static int hclge_tm_schd_mode_vnet_base_cfg(struct hclge_vport *vport)
{
	struct hnae3_knic_private_info *kinfo = &vport->nic.kinfo;
	struct hclge_dev *hdev = vport->back;
	int ret;
	u8 i;

	if (vport->vport_id >= HNAE3_MAX_TC)
		return -EINVAL;

	ret = hclge_tm_pri_schd_mode_cfg(hdev, vport->vport_id);
	if (ret)
		return ret;

	for (i = 0; i < kinfo->num_tc; i++) {
		u8 sch_mode = hdev->tm_info.tc_info[i].tc_sch_mode;

		ret = hclge_tm_qs_schd_mode_cfg(hdev, vport->qs_offset + i,
						sch_mode);
		if (ret)
			return ret;
	}

	return 0;
}