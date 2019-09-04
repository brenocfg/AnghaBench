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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ fc_mode; } ;
struct hclge_dev {scalar_t__ fc_mode_last_time; TYPE_2__ tm_info; TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ HCLGE_FC_FULL ; 
 scalar_t__ HCLGE_FC_NONE ; 
 scalar_t__ HCLGE_FC_PFC ; 
 scalar_t__ HCLGE_FC_RX_PAUSE ; 
 scalar_t__ HCLGE_FC_TX_PAUSE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_mac_pause_en_cfg (struct hclge_dev*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int hclge_cfg_pauseparam(struct hclge_dev *hdev, u32 rx_en, u32 tx_en)
{
	int ret;

	if (rx_en && tx_en)
		hdev->fc_mode_last_time = HCLGE_FC_FULL;
	else if (rx_en && !tx_en)
		hdev->fc_mode_last_time = HCLGE_FC_RX_PAUSE;
	else if (!rx_en && tx_en)
		hdev->fc_mode_last_time = HCLGE_FC_TX_PAUSE;
	else
		hdev->fc_mode_last_time = HCLGE_FC_NONE;

	if (hdev->tm_info.fc_mode == HCLGE_FC_PFC)
		return 0;

	ret = hclge_mac_pause_en_cfg(hdev, tx_en, rx_en);
	if (ret) {
		dev_err(&hdev->pdev->dev, "configure pauseparam error, ret = %d.\n",
			ret);
		return ret;
	}

	hdev->tm_info.fc_mode = hdev->fc_mode_last_time;

	return 0;
}