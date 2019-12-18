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
typedef  int /*<<< orphan*/  u16 ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_mbx_vf_to_pf_cmd {int* msg; int /*<<< orphan*/  msg_len; int /*<<< orphan*/  mbx_src_vfid; } ;
struct hclge_mbx_pf_to_vf_cmd {int* msg; int /*<<< orphan*/  msg_len; int /*<<< orphan*/  dest_vfid; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
typedef  enum hclge_cmd_status { ____Placeholder_hclge_cmd_status } hclge_cmd_status ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_OPC_MBX_PF_TO_VF ; 
 int /*<<< orphan*/  HCLGE_MBX_MAX_RESP_DATA_SIZE ; 
 int HCLGE_MBX_PF_VF_RESP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_gen_resp_to_vf(struct hclge_vport *vport,
				struct hclge_mbx_vf_to_pf_cmd *vf_to_pf_req,
				int resp_status,
				u8 *resp_data, u16 resp_data_len)
{
	struct hclge_mbx_pf_to_vf_cmd *resp_pf_to_vf;
	struct hclge_dev *hdev = vport->back;
	enum hclge_cmd_status status;
	struct hclge_desc desc;

	resp_pf_to_vf = (struct hclge_mbx_pf_to_vf_cmd *)desc.data;

	if (resp_data_len > HCLGE_MBX_MAX_RESP_DATA_SIZE) {
		dev_err(&hdev->pdev->dev,
			"PF fail to gen resp to VF len %d exceeds max len %d\n",
			resp_data_len,
			HCLGE_MBX_MAX_RESP_DATA_SIZE);
		/* If resp_data_len is too long, set the value to max length
		 * and return the msg to VF
		 */
		resp_data_len = HCLGE_MBX_MAX_RESP_DATA_SIZE;
	}

	hclge_cmd_setup_basic_desc(&desc, HCLGEVF_OPC_MBX_PF_TO_VF, false);

	resp_pf_to_vf->dest_vfid = vf_to_pf_req->mbx_src_vfid;
	resp_pf_to_vf->msg_len = vf_to_pf_req->msg_len;

	resp_pf_to_vf->msg[0] = HCLGE_MBX_PF_VF_RESP;
	resp_pf_to_vf->msg[1] = vf_to_pf_req->msg[0];
	resp_pf_to_vf->msg[2] = vf_to_pf_req->msg[1];
	resp_pf_to_vf->msg[3] = (resp_status == 0) ? 0 : 1;

	if (resp_data && resp_data_len > 0)
		memcpy(&resp_pf_to_vf->msg[4], resp_data, resp_data_len);

	status = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (status)
		dev_err(&hdev->pdev->dev,
			"PF failed(=%d) to send response to VF\n", status);

	return status;
}