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
struct TYPE_4__ {scalar_t__ fc_mode; } ;
struct hclge_dev {int flag; scalar_t__ fc_mode_last_time; TYPE_2__ tm_info; TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ HCLGE_FC_PFC ; 
 int HCLGE_FLAG_DCB_ENABLE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void hclge_pfc_info_init(struct hclge_dev *hdev)
{
	if (!(hdev->flag & HCLGE_FLAG_DCB_ENABLE)) {
		if (hdev->fc_mode_last_time == HCLGE_FC_PFC)
			dev_warn(&hdev->pdev->dev,
				 "DCB is disable, but last mode is FC_PFC\n");

		hdev->tm_info.fc_mode = hdev->fc_mode_last_time;
	} else if (hdev->tm_info.fc_mode != HCLGE_FC_PFC) {
		/* fc_mode_last_time record the last fc_mode when
		 * DCB is enabled, so that fc_mode can be set to
		 * the correct value when DCB is disabled.
		 */
		hdev->fc_mode_last_time = hdev->tm_info.fc_mode;
		hdev->tm_info.fc_mode = HCLGE_FC_PFC;
	}
}