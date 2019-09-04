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
struct hclge_vport {int /*<<< orphan*/  vport_id; struct hclge_dev* back; } ;
struct hclge_mbx_vf_to_pf_cmd {int /*<<< orphan*/  mbx_src_vfid; } ;
struct hclge_dev {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hclge_func_reset_cmd (struct hclge_dev*,int /*<<< orphan*/ ) ; 
 int hclge_inform_reset_assert_to_vf (struct hclge_vport*) ; 

__attribute__((used)) static void hclge_reset_vf(struct hclge_vport *vport,
			   struct hclge_mbx_vf_to_pf_cmd *mbx_req)
{
	struct hclge_dev *hdev = vport->back;
	int ret;

	dev_warn(&hdev->pdev->dev, "PF received VF reset request from VF %d!",
		 mbx_req->mbx_src_vfid);

	/* Acknowledge VF that PF is now about to assert the reset for the VF.
	 * On receiving this message VF will get into pending state and will
	 * start polling for the hardware reset completion status.
	 */
	ret = hclge_inform_reset_assert_to_vf(vport);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"PF fail(%d) to inform VF(%d)of reset, reset failed!\n",
			ret, vport->vport_id);
		return;
	}

	dev_warn(&hdev->pdev->dev, "PF is now resetting VF %d.\n",
		 mbx_req->mbx_src_vfid);
	/* reset this virtual function */
	hclge_func_reset_cmd(hdev, mbx_req->mbx_src_vfid);
}