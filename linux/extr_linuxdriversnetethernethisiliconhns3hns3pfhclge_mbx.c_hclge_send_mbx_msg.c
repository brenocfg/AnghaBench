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
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u16 ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_mbx_pf_to_vf_cmd {void** msg; void* msg_len; int /*<<< orphan*/  dest_vfid; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
typedef  enum hclge_cmd_status { ____Placeholder_hclge_cmd_status } hclge_cmd_status ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_OPC_MBX_PF_TO_VF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (void**,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int hclge_send_mbx_msg(struct hclge_vport *vport, u8 *msg, u16 msg_len,
			      u16 mbx_opcode, u8 dest_vfid)
{
	struct hclge_mbx_pf_to_vf_cmd *resp_pf_to_vf;
	struct hclge_dev *hdev = vport->back;
	enum hclge_cmd_status status;
	struct hclge_desc desc;

	resp_pf_to_vf = (struct hclge_mbx_pf_to_vf_cmd *)desc.data;

	hclge_cmd_setup_basic_desc(&desc, HCLGEVF_OPC_MBX_PF_TO_VF, false);

	resp_pf_to_vf->dest_vfid = dest_vfid;
	resp_pf_to_vf->msg_len = msg_len;
	resp_pf_to_vf->msg[0] = mbx_opcode;

	memcpy(&resp_pf_to_vf->msg[1], msg, msg_len);

	status = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (status)
		dev_err(&hdev->pdev->dev,
			"PF failed(=%d) to send mailbox message to VF\n",
			status);

	return status;
}