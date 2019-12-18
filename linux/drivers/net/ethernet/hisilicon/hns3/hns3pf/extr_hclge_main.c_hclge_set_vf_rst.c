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
struct hclge_vf_rst_cmd {int dest_vfid; int vf_rst; } ;
struct hclge_dev {int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_OPC_GBL_RST_STATUS ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclge_set_vf_rst(struct hclge_dev *hdev, int func_id, bool reset)
{
	struct hclge_vf_rst_cmd *req;
	struct hclge_desc desc;

	req = (struct hclge_vf_rst_cmd *)desc.data;
	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_GBL_RST_STATUS, false);
	req->dest_vfid = func_id;

	if (reset)
		req->vf_rst = 0x1;

	return hclge_cmd_send(&hdev->hw, &desc, 1);
}