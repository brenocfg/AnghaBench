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
typedef  scalar_t__ u16 ;
struct hclge_vport {int dummy; } ;
struct hclge_dev {scalar_t__ num_vmdq_vport; scalar_t__ num_req_vfs; struct hclge_vport* vport; } ;

/* Variables and functions */
 int hclge_map_tqp_to_vport (struct hclge_dev*,struct hclge_vport*) ; 

__attribute__((used)) static int hclge_map_tqp(struct hclge_dev *hdev)
{
	struct hclge_vport *vport = hdev->vport;
	u16 i, num_vport;

	num_vport = hdev->num_vmdq_vport + hdev->num_req_vfs + 1;
	for (i = 0; i < num_vport; i++)	{
		int ret;

		ret = hclge_map_tqp_to_vport(hdev, vport);
		if (ret)
			return ret;

		vport++;
	}

	return 0;
}