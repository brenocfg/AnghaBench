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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {scalar_t__ fc_mode; } ;
struct hclge_dev {TYPE_2__* pdev; TYPE_1__ tm_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ HCLGE_FC_PFC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_mac_pause_en_cfg (struct hclge_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_cfg_pauseparam(struct hclge_dev *hdev, u32 rx_en, u32 tx_en)
{
	int ret;

	if (hdev->tm_info.fc_mode == HCLGE_FC_PFC)
		return 0;

	ret = hclge_mac_pause_en_cfg(hdev, tx_en, rx_en);
	if (ret)
		dev_err(&hdev->pdev->dev,
			"configure pauseparam error, ret = %d.\n", ret);

	return ret;
}