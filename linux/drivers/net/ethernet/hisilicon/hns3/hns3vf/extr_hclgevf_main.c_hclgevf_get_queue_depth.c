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
struct hclgevf_dev {int /*<<< orphan*/  num_rx_desc; int /*<<< orphan*/  num_tx_desc; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HCLGEVF_TQPS_DEPTH_INFO_LEN ; 
 int /*<<< orphan*/  HCLGE_MBX_GET_QDEPTH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclgevf_send_mbx_msg (struct hclgevf_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hclgevf_get_queue_depth(struct hclgevf_dev *hdev)
{
#define HCLGEVF_TQPS_DEPTH_INFO_LEN	4
	u8 resp_msg[HCLGEVF_TQPS_DEPTH_INFO_LEN];
	int ret;

	ret = hclgevf_send_mbx_msg(hdev, HCLGE_MBX_GET_QDEPTH, 0, NULL, 0,
				   true, resp_msg,
				   HCLGEVF_TQPS_DEPTH_INFO_LEN);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"VF request to get tqp depth info from PF failed %d",
			ret);
		return ret;
	}

	memcpy(&hdev->num_tx_desc, &resp_msg[0], sizeof(u16));
	memcpy(&hdev->num_rx_desc, &resp_msg[2], sizeof(u16));

	return 0;
}