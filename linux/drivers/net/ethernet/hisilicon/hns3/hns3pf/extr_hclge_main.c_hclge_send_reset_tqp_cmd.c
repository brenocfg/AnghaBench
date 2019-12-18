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
typedef  int u16 ;
struct hclge_reset_tqp_queue_cmd {int /*<<< orphan*/  reset_req; int /*<<< orphan*/  tqp_id; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_OPC_RESET_TQP_QUEUE ; 
 int HCLGE_RING_ID_MASK ; 
 int /*<<< orphan*/  HCLGE_TQP_RESET_B ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hnae3_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int hclge_send_reset_tqp_cmd(struct hclge_dev *hdev, u16 queue_id,
				    bool enable)
{
	struct hclge_reset_tqp_queue_cmd *req;
	struct hclge_desc desc;
	int ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_RESET_TQP_QUEUE, false);

	req = (struct hclge_reset_tqp_queue_cmd *)desc.data;
	req->tqp_id = cpu_to_le16(queue_id & HCLGE_RING_ID_MASK);
	if (enable)
		hnae3_set_bit(req->reset_req, HCLGE_TQP_RESET_B, 1U);

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"Send tqp reset cmd error, status =%d\n", ret);
		return ret;
	}

	return 0;
}