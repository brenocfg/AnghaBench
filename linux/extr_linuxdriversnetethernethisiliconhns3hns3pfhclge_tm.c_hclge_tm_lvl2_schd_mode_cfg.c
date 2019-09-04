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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {scalar_t__ num_pg; } ;
struct hclge_dev {scalar_t__ tx_sch_mode; TYPE_1__ tm_info; } ;

/* Variables and functions */
 scalar_t__ HCLGE_FLAG_VNET_BASE_SCH_MODE ; 
 int hclge_tm_pg_schd_mode_cfg (struct hclge_dev*,scalar_t__) ; 

__attribute__((used)) static int hclge_tm_lvl2_schd_mode_cfg(struct hclge_dev *hdev)
{
	int ret;
	u8 i;

	/* Only being config on TC-Based scheduler mode */
	if (hdev->tx_sch_mode == HCLGE_FLAG_VNET_BASE_SCH_MODE)
		return 0;

	for (i = 0; i < hdev->tm_info.num_pg; i++) {
		ret = hclge_tm_pg_schd_mode_cfg(hdev, i);
		if (ret)
			return ret;
	}

	return 0;
}