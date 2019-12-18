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
struct hclgevf_cfg_com_tqp_queue_cmd {unsigned int enable; void* stream_id; void* tqp_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_OPC_CFG_COM_TQP_QUEUE ; 
 unsigned int HCLGEVF_RING_ID_MASK ; 
 unsigned int HCLGEVF_TQP_ENABLE_B ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclgevf_cmd_send (int /*<<< orphan*/ *,struct hclgevf_desc*,int) ; 
 int /*<<< orphan*/  hclgevf_cmd_setup_basic_desc (struct hclgevf_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclgevf_tqp_enable(struct hclgevf_dev *hdev, unsigned int tqp_id,
			      int stream_id, bool enable)
{
	struct hclgevf_cfg_com_tqp_queue_cmd *req;
	struct hclgevf_desc desc;
	int status;

	req = (struct hclgevf_cfg_com_tqp_queue_cmd *)desc.data;

	hclgevf_cmd_setup_basic_desc(&desc, HCLGEVF_OPC_CFG_COM_TQP_QUEUE,
				     false);
	req->tqp_id = cpu_to_le16(tqp_id & HCLGEVF_RING_ID_MASK);
	req->stream_id = cpu_to_le16(stream_id);
	if (enable)
		req->enable |= 1U << HCLGEVF_TQP_ENABLE_B;

	status = hclgevf_cmd_send(&hdev->hw, &desc, 1);
	if (status)
		dev_err(&hdev->pdev->dev,
			"TQP enable fail, status =%d.\n", status);

	return status;
}