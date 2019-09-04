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
struct hclge_vport {scalar_t__ qs_offset; int /*<<< orphan*/  dwrr; int /*<<< orphan*/  vport_id; struct hclge_dev* back; TYPE_3__ nic; } ;
struct TYPE_5__ {TYPE_1__* pg_info; } ;
struct hclge_dev {TYPE_2__ tm_info; } ;
struct TYPE_4__ {int /*<<< orphan*/ * tc_dwrr; } ;

/* Variables and functions */
 int hclge_tm_pri_weight_cfg (struct hclge_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hclge_tm_qs_weight_cfg (struct hclge_dev*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_tm_pri_vnet_base_dwrr_pri_cfg(struct hclge_vport *vport)
{
	struct hnae3_knic_private_info *kinfo = &vport->nic.kinfo;
	struct hclge_dev *hdev = vport->back;
	int ret;
	u8 i;

	/* Vf dwrr */
	ret = hclge_tm_pri_weight_cfg(hdev, vport->vport_id, vport->dwrr);
	if (ret)
		return ret;

	/* Qset dwrr */
	for (i = 0; i < kinfo->num_tc; i++) {
		ret = hclge_tm_qs_weight_cfg(
			hdev, vport->qs_offset + i,
			hdev->tm_info.pg_info[0].tc_dwrr[i]);
		if (ret)
			return ret;
	}

	return 0;
}