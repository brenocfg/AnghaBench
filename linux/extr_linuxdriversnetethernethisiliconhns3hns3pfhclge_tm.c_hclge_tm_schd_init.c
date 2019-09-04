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
struct TYPE_2__ {int /*<<< orphan*/  fc_mode; } ;
struct hclge_dev {TYPE_1__ tm_info; int /*<<< orphan*/  fc_mode_last_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_FC_FULL ; 
 int hclge_tm_init_hw (struct hclge_dev*) ; 
 int hclge_tm_schd_info_init (struct hclge_dev*) ; 

int hclge_tm_schd_init(struct hclge_dev *hdev)
{
	int ret;

	/* fc_mode is HCLGE_FC_FULL on reset */
	hdev->tm_info.fc_mode = HCLGE_FC_FULL;
	hdev->fc_mode_last_time = hdev->tm_info.fc_mode;

	ret = hclge_tm_schd_info_init(hdev);
	if (ret)
		return ret;

	return hclge_tm_init_hw(hdev);
}