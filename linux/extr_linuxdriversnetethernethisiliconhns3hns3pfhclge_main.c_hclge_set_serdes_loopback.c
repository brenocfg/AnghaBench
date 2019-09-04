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
struct hclge_serdes_lb_cmd {int result; void* mask; void* enable; } ;
struct hclge_dev {TYPE_1__* pdev; int /*<<< orphan*/  hw; } ;
struct hclge_desc {int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int HCLGE_CMD_SERDES_DONE_B ; 
 void* HCLGE_CMD_SERDES_SERIAL_INNER_LOOP_B ; 
 int HCLGE_CMD_SERDES_SUCCESS_B ; 
 int /*<<< orphan*/  HCLGE_OPC_SERDES_LOOPBACK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int hclge_cmd_send (int /*<<< orphan*/ *,struct hclge_desc*,int) ; 
 int /*<<< orphan*/  hclge_cmd_setup_basic_desc (struct hclge_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int hclge_set_serdes_loopback(struct hclge_dev *hdev, bool en)
{
#define HCLGE_SERDES_RETRY_MS	10
#define HCLGE_SERDES_RETRY_NUM	100
	struct hclge_serdes_lb_cmd *req;
	struct hclge_desc desc;
	int ret, i = 0;

	req = (struct hclge_serdes_lb_cmd *)&desc.data[0];
	hclge_cmd_setup_basic_desc(&desc, HCLGE_OPC_SERDES_LOOPBACK, false);

	if (en) {
		req->enable = HCLGE_CMD_SERDES_SERIAL_INNER_LOOP_B;
		req->mask = HCLGE_CMD_SERDES_SERIAL_INNER_LOOP_B;
	} else {
		req->mask = HCLGE_CMD_SERDES_SERIAL_INNER_LOOP_B;
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

	return 0;
}