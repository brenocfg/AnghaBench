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
struct hclgevf_dev {TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  resp_msg ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_MBX_GET_LINK_STATUS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclgevf_send_mbx_msg (struct hclgevf_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void hclgevf_request_link_info(struct hclgevf_dev *hdev)
{
	int status;
	u8 resp_msg;

	status = hclgevf_send_mbx_msg(hdev, HCLGE_MBX_GET_LINK_STATUS, 0, NULL,
				      0, false, &resp_msg, sizeof(resp_msg));
	if (status)
		dev_err(&hdev->pdev->dev,
			"VF failed to fetch link status(%d) from PF", status);
}