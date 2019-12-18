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
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
struct hclge_cfg_com_tqp_queue_cmd {unsigned int enable; void* stream_id; void* tqp_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_OPC_CFG_COM_TQP_QUEUE ; 
 unsigned int HCLGE_RING_ID_MASK ; 
 unsigned int HCLGE_TQP_ENABLE_B ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hclge_tqp_enable(struct hclge_dev *hdev, unsigned int tqp_id,
			    int stream_id, bool enable)
{
	struct hclge_desc desc;
	struct hclge_cfg_com_tqp_queue_cmd *req =
		(struct hclge_cfg_com_tqp_queue_cmd *)desc.data;
	int ret;

	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_CFG_COM_TQP_QUEUE, false);
	req->tqp_id = cpu_to_le16(tqp_id & HCLGE_RING_ID_MASK);
	req->stream_id = cpu_to_le16(stream_id);
	if (enable)
		req->enable |= 1U << HCLGE_TQP_ENABLE_B;

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret)
		dev_err(&hdev->pdev->dev,
			"Tqp enable fail, status =%d.\n", ret);
	return ret;
}