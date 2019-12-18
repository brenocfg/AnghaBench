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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  fc_mode; } ;
struct hclge_dev {int /*<<< orphan*/  fc_mode_last_time; TYPE_1__ tm_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_FC_FULL ; 
 int /*<<< orphan*/  HCLGE_FC_NONE ; 
 int /*<<< orphan*/  HCLGE_FC_RX_PAUSE ; 
 int /*<<< orphan*/  HCLGE_FC_TX_PAUSE ; 

__attribute__((used)) static void hclge_record_user_pauseparam(struct hclge_dev *hdev,
					 u32 rx_en, u32 tx_en)
{
	if (rx_en && tx_en)
		hdev->fc_mode_last_time = HCLGE_FC_FULL;
	else if (rx_en && !tx_en)
		hdev->fc_mode_last_time = HCLGE_FC_RX_PAUSE;
	else if (!rx_en && tx_en)
		hdev->fc_mode_last_time = HCLGE_FC_TX_PAUSE;
	else
		hdev->fc_mode_last_time = HCLGE_FC_NONE;

	hdev->tm_info.fc_mode = hdev->fc_mode_last_time;
}