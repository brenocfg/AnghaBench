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
struct hclge_vport {int dummy; } ;
struct hclge_dev {int flag; struct hclge_vport* vport; } ;

/* Variables and functions */
 int HCLGE_FLAG_DCB_ENABLE ; 
 int hclge_tm_bp_setup (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_tm_vport_tc_info_update (struct hclge_vport*) ; 
 int hclge_vport_q_to_qs_map (struct hclge_dev*,struct hclge_vport*) ; 

int hclge_tm_vport_map_update(struct hclge_dev *hdev)
{
	struct hclge_vport *vport = hdev->vport;
	int ret;

	hclge_tm_vport_tc_info_update(vport);

	ret = hclge_vport_q_to_qs_map(hdev, vport);
	if (ret)
		return ret;

	if (!(hdev->flag & HCLGE_FLAG_DCB_ENABLE))
		return 0;

	return hclge_tm_bp_setup(hdev);
}