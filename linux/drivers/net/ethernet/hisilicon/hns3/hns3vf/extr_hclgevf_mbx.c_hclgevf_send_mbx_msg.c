#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  void* u16 ;
struct TYPE_3__ {int /*<<< orphan*/  mbx_mutex; } ;
struct hclgevf_dev {TYPE_2__* pdev; int /*<<< orphan*/  hw; TYPE_1__ mbx_resp; } ;
struct hclgevf_desc {scalar_t__ data; } ;
struct hclge_mbx_vf_to_pf_cmd {void** msg; int /*<<< orphan*/  mbx_need_resp; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HCLGEVF_OPC_MBX_VF_TO_PF ; 
 int HCLGE_MBX_MAX_MSG_SIZE ; 
 int /*<<< orphan*/  HCLGE_MBX_NEED_RESP_BIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int hclgevf_cmd_send (int /*<<< orphan*/ *,struct hclgevf_desc*,int) ; 
 int /*<<< orphan*/  hclgevf_cmd_setup_basic_desc (struct hclgevf_desc*,int /*<<< orphan*/ ,int) ; 
 int hclgevf_get_mbx_resp (struct hclgevf_dev*,void*,void*,int*,void*) ; 
 int /*<<< orphan*/  hclgevf_reset_mbx_resp_status (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  memcpy (void**,int const*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int hclgevf_send_mbx_msg(struct hclgevf_dev *hdev, u16 code, u16 subcode,
			 const u8 *msg_data, u8 msg_len, bool need_resp,
			 u8 *resp_data, u16 resp_len)
{
	struct hclge_mbx_vf_to_pf_cmd *req;
	struct hclgevf_desc desc;
	int status;

	req = (struct hclge_mbx_vf_to_pf_cmd *)desc.data;

	/* first two bytes are reserved for code & subcode */
	if (msg_len > (HCLGE_MBX_MAX_MSG_SIZE - 2)) {
		dev_err(&hdev->pdev->dev,
			"VF send mbx msg fail, msg len %d exceeds max len %d\n",
			msg_len, HCLGE_MBX_MAX_MSG_SIZE);
		return -EINVAL;
	}

	hclgevf_cmd_setup_basic_desc(&desc, HCLGEVF_OPC_MBX_VF_TO_PF, false);
	req->mbx_need_resp |= need_resp ? HCLGE_MBX_NEED_RESP_BIT :
					  ~HCLGE_MBX_NEED_RESP_BIT;
	req->msg[0] = code;
	req->msg[1] = subcode;
	if (msg_data)
		memcpy(&req->msg[2], msg_data, msg_len);

	/* synchronous send */
	if (need_resp) {
		mutex_lock(&hdev->mbx_resp.mbx_mutex);
		hclgevf_reset_mbx_resp_status(hdev);
		status = hclgevf_cmd_send(&hdev->hw, &desc, 1);
		if (status) {
			dev_err(&hdev->pdev->dev,
				"VF failed(=%d) to send mbx message to PF\n",
				status);
			mutex_unlock(&hdev->mbx_resp.mbx_mutex);
			return status;
		}

		status = hclgevf_get_mbx_resp(hdev, code, subcode, resp_data,
					      resp_len);
		mutex_unlock(&hdev->mbx_resp.mbx_mutex);
	} else {
		/* asynchronous send */
		status = hclgevf_cmd_send(&hdev->hw, &desc, 1);
		if (status) {
			dev_err(&hdev->pdev->dev,
				"VF failed(=%d) to send mbx message to PF\n",
				status);
			return status;
		}
	}

	return status;
}