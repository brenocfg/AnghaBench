#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct hnae3_tc_info {size_t tqp_count; size_t tqp_offset; } ;
struct hnae3_queue {int dummy; } ;
struct hnae3_knic_private_info {size_t num_tc; struct hnae3_tc_info* tc_info; struct hnae3_queue** tqp; } ;
struct TYPE_2__ {struct hnae3_knic_private_info kinfo; } ;
struct hclge_vport {size_t qs_offset; TYPE_1__ nic; } ;
struct hclge_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hclge_get_queue_id (struct hnae3_queue*) ; 
 int hclge_tm_q_to_qs_map_cfg (struct hclge_dev*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int hclge_vport_q_to_qs_map(struct hclge_dev *hdev,
				   struct hclge_vport *vport)
{
	struct hnae3_knic_private_info *kinfo = &vport->nic.kinfo;
	struct hnae3_queue **tqp = kinfo->tqp;
	struct hnae3_tc_info *v_tc_info;
	u32 i, j;
	int ret;

	for (i = 0; i < kinfo->num_tc; i++) {
		v_tc_info = &kinfo->tc_info[i];
		for (j = 0; j < v_tc_info->tqp_count; j++) {
			struct hnae3_queue *q = tqp[v_tc_info->tqp_offset + j];

			ret = hclge_tm_q_to_qs_map_cfg(hdev,
						       hclge_get_queue_id(q),
						       vport->qs_offset + i);
			if (ret)
				return ret;
		}
	}

	return 0;
}