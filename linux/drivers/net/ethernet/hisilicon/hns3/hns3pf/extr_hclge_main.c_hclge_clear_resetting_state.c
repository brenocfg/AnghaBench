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
typedef  size_t u16 ;
struct hclge_vport {int /*<<< orphan*/  vport_id; } ;
struct hclge_dev {size_t num_alloc_vport; TYPE_1__* pdev; struct hclge_vport* vport; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int hclge_set_vf_rst (struct hclge_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hclge_clear_resetting_state(struct hclge_dev *hdev)
{
	u16 i;

	for (i = 0; i < hdev->num_alloc_vport; i++) {
		struct hclge_vport *vport = &hdev->vport[i];
		int ret;

		 /* Send cmd to clear VF's FUNC_RST_ING */
		ret = hclge_set_vf_rst(hdev, vport->vport_id, false);
		if (ret)
			dev_warn(&hdev->pdev->dev,
				 "clear vf(%d) rst failed %d!\n",
				 vport->vport_id, ret);
	}
}