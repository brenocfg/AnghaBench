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
struct TYPE_2__ {int num_pg; int /*<<< orphan*/  fc_mode; } ;
struct hclge_dev {scalar_t__ tx_sch_mode; TYPE_1__ tm_info; int /*<<< orphan*/  fc_mode_last_time; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HCLGE_FC_FULL ; 
 scalar_t__ HCLGE_FLAG_TC_BASE_SCH_MODE ; 
 int hclge_tm_init_hw (struct hclge_dev*,int) ; 
 int /*<<< orphan*/  hclge_tm_schd_info_init (struct hclge_dev*) ; 

int hclge_tm_schd_init(struct hclge_dev *hdev)
{
	/* fc_mode is HCLGE_FC_FULL on reset */
	hdev->tm_info.fc_mode = HCLGE_FC_FULL;
	hdev->fc_mode_last_time = hdev->tm_info.fc_mode;

	if (hdev->tx_sch_mode != HCLGE_FLAG_TC_BASE_SCH_MODE &&
	    hdev->tm_info.num_pg != 1)
		return -EINVAL;

	hclge_tm_schd_info_init(hdev);

	return hclge_tm_init_hw(hdev, true);
}