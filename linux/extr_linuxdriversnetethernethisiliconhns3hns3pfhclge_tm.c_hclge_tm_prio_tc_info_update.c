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
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
struct hnae3_knic_private_info {scalar_t__* prio_tc; } ;
struct TYPE_4__ {struct hnae3_knic_private_info kinfo; } ;
struct hclge_vport {TYPE_2__ nic; } ;
struct TYPE_3__ {scalar_t__ num_tc; scalar_t__* prio_tc; } ;
struct hclge_dev {size_t num_alloc_vport; TYPE_1__ tm_info; struct hclge_vport* vport; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t HNAE3_MAX_USER_PRIO ; 

int hclge_tm_prio_tc_info_update(struct hclge_dev *hdev, u8 *prio_tc)
{
	struct hclge_vport *vport = hdev->vport;
	struct hnae3_knic_private_info *kinfo;
	u32 i, k;

	for (i = 0; i < HNAE3_MAX_USER_PRIO; i++) {
		if (prio_tc[i] >= hdev->tm_info.num_tc)
			return -EINVAL;
		hdev->tm_info.prio_tc[i] = prio_tc[i];

		for (k = 0;  k < hdev->num_alloc_vport; k++) {
			kinfo = &vport[k].nic.kinfo;
			kinfo->prio_tc[i] = prio_tc[i];
		}
	}
	return 0;
}