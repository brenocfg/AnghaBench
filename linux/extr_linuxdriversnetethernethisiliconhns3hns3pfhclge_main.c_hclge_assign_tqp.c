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
struct hnae3_knic_private_info {int num_tqps; TYPE_2__** tqp; int /*<<< orphan*/  num_desc; } ;
struct TYPE_4__ {struct hnae3_knic_private_info kinfo; } ;
struct hclge_vport {int alloc_tqps; TYPE_1__ nic; struct hclge_dev* back; } ;
struct hclge_dev {int num_tqps; TYPE_3__* htqp; } ;
struct TYPE_5__ {int tqp_index; int /*<<< orphan*/  desc_num; TYPE_1__* handle; } ;
struct TYPE_6__ {int alloced; TYPE_2__ q; } ;

/* Variables and functions */

__attribute__((used)) static int  hclge_assign_tqp(struct hclge_vport *vport)
{
	struct hnae3_knic_private_info *kinfo = &vport->nic.kinfo;
	struct hclge_dev *hdev = vport->back;
	int i, alloced;

	for (i = 0, alloced = 0; i < hdev->num_tqps &&
	     alloced < kinfo->num_tqps; i++) {
		if (!hdev->htqp[i].alloced) {
			hdev->htqp[i].q.handle = &vport->nic;
			hdev->htqp[i].q.tqp_index = alloced;
			hdev->htqp[i].q.desc_num = kinfo->num_desc;
			kinfo->tqp[alloced] = &hdev->htqp[i].q;
			hdev->htqp[i].alloced = true;
			alloced++;
		}
	}
	vport->alloc_tqps = kinfo->num_tqps;

	return 0;
}