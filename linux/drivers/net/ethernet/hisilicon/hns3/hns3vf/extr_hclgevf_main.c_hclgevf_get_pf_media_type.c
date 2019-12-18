#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
struct TYPE_6__ {void* module_type; void* media_type; } ;
struct TYPE_5__ {TYPE_3__ mac; } ;
struct hclgevf_dev {TYPE_2__ hw; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  resp_msg ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_MBX_GET_MEDIA_TYPE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclgevf_send_mbx_msg (struct hclgevf_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,void**,int) ; 

__attribute__((used)) static int hclgevf_get_pf_media_type(struct hclgevf_dev *hdev)
{
	u8 resp_msg[2];
	int ret;

	ret = hclgevf_send_mbx_msg(hdev, HCLGE_MBX_GET_MEDIA_TYPE, 0, NULL, 0,
				   true, resp_msg, sizeof(resp_msg));
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"VF request to get the pf port media type failed %d",
			ret);
		return ret;
	}

	hdev->hw.mac.media_type = resp_msg[0];
	hdev->hw.mac.module_type = resp_msg[1];

	return 0;
}