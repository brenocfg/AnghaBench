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
struct hclgevf_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclgevf_desc {scalar_t__ data; } ;
struct hclge_mbx_vf_to_pf_cmd {int* msg; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_OPC_MBX_VF_TO_PF ; 
 int HCLGE_MBX_SET_PROMISC_MODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclgevf_cmd_send (int /*<<< orphan*/ *,struct hclgevf_desc*,int) ; 
 int /*<<< orphan*/  hclgevf_cmd_setup_basic_desc (struct hclgevf_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclgevf_cmd_set_promisc_mode(struct hclgevf_dev *hdev,
					bool en_bc_pmc)
{
	struct hclge_mbx_vf_to_pf_cmd *req;
	struct hclgevf_desc desc;
	int ret;

	req = (struct hclge_mbx_vf_to_pf_cmd *)desc.data;

	hclgevf_cmd_setup_basic_desc(&desc, HCLGEVF_OPC_MBX_VF_TO_PF, false);
	req->msg[0] = HCLGE_MBX_SET_PROMISC_MODE;
	req->msg[1] = en_bc_pmc ? 1 : 0;

	ret = hclgevf_cmd_send(&hdev->hw, &desc, 1);
	if (ret)
		dev_err(&hdev->pdev->dev,
			"Set promisc mode fail, status is %d.\n", ret);

	return ret;
}