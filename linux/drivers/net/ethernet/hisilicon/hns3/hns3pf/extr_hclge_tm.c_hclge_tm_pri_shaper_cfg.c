#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hclge_dev {scalar_t__ tx_sch_mode; } ;

/* Variables and functions */
 scalar_t__ HCLGE_FLAG_TC_BASE_SCH_MODE ; 
 int hclge_tm_pri_tc_base_shaper_cfg (struct hclge_dev*) ; 
 int hclge_tm_pri_vnet_base_shaper_cfg (struct hclge_dev*) ; 

__attribute__((used)) static int hclge_tm_pri_shaper_cfg(struct hclge_dev *hdev)
{
	int ret;

	if (hdev->tx_sch_mode == HCLGE_FLAG_TC_BASE_SCH_MODE) {
		ret = hclge_tm_pri_tc_base_shaper_cfg(hdev);
		if (ret)
			return ret;
	} else {
		ret = hclge_tm_pri_vnet_base_shaper_cfg(hdev);
		if (ret)
			return ret;
	}

	return 0;
}