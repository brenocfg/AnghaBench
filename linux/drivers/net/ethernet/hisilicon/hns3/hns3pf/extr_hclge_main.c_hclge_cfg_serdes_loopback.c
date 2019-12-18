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
typedef  void* u8 ;
struct hclge_serdes_lb_cmd {int result; void* mask; void* enable; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {scalar_t__ data; } ;
typedef  enum hnae3_loop { ____Placeholder_hnae3_loop } hnae3_loop ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int ENOTSUPP ; 
 int HCLGE_CMD_SERDES_DONE_B ; 
 void* HCLGE_CMD_SERDES_PARALLEL_INNER_LOOP_B ; 
 void* HCLGE_CMD_SERDES_SERIAL_INNER_LOOP_B ; 
 int HCLGE_CMD_SERDES_SUCCESS_B ; 
 int /*<<< orphan*/  HCLGE_OPC_SERDES_LOOPBACK ; 
 int /*<<< orphan*/  HCLGE_SERDES_RETRY_MS ; 
 int HCLGE_SERDES_RETRY_NUM ; 
#define  HNAE3_LOOP_PARALLEL_SERDES 129 
#define  HNAE3_LOOP_SERIAL_SERDES 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_cfg_serdes_loopback(struct hclge_dev *hdev, bool en,
				     enum hnae3_loop loop_mode)
{
#define HCLGE_SERDES_RETRY_MS	10
#define HCLGE_SERDES_RETRY_NUM	100

	struct hclge_serdes_lb_cmd *req;
	struct hclge_desc desc;
	int ret, i = 0;
	u8 loop_mode_b;

	req = (struct hclge_serdes_lb_cmd *)desc.data;
	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_SERDES_LOOPBACK, false);

	switch (loop_mode) {
	case HNAE3_LOOP_SERIAL_SERDES:
		loop_mode_b = HCLGE_CMD_SERDES_SERIAL_INNER_LOOP_B;
		break;
	case HNAE3_LOOP_PARALLEL_SERDES:
		loop_mode_b = HCLGE_CMD_SERDES_PARALLEL_INNER_LOOP_B;
		break;
	default:
		dev_err(&hdev->pdev->dev,
			"unsupported serdes loopback mode %d\n", loop_mode);
		return -ENOTSUPP;
	}

	if (en) {
		req->enable = loop_mode_b;
		req->mask = loop_mode_b;
	} else {
		req->mask = loop_mode_b;
	}

	ret = hclge_cmd_send(&hdev->hw, &desc, 1);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"serdes loopback set fail, ret = %d\n", ret);
		return ret;
	}

	do {
		msleep(HCLGE_SERDES_RETRY_MS);
		hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_SERDES_LOOPBACK,
					   true);
		ret = hclge_cmd_send(&hdev->hw, &desc, 1);
		if (ret) {
			dev_err(&hdev->pdev->dev,
				"serdes loopback get, ret = %d\n", ret);
			return ret;
		}
	} while (++i < HCLGE_SERDES_RETRY_NUM &&
		 !(req->result & HCLGE_CMD_SERDES_DONE_B));

	if (!(req->result & HCLGE_CMD_SERDES_DONE_B)) {
		dev_err(&hdev->pdev->dev, "serdes loopback set timeout\n");
		return -EBUSY;
	} else if (!(req->result & HCLGE_CMD_SERDES_SUCCESS_B)) {
		dev_err(&hdev->pdev->dev, "serdes loopback set failed in fw\n");
		return -EIO;
	}
	return ret;
}