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
 int ENOTSUPP ; 
 scalar_t__ HCLGE_FLAG_TC_BASE_SCH_MODE ; 
 scalar_t__ HCLGE_FLAG_VNET_BASE_SCH_MODE ; 
 int hclge_pause_setup_hw (struct hclge_dev*,int) ; 
 int hclge_tm_schd_setup_hw (struct hclge_dev*) ; 

int hclge_tm_init_hw(struct hclge_dev *hdev, bool init)
{
	int ret;

	if ((hdev->tx_sch_mode != HCLGE_FLAG_TC_BASE_SCH_MODE) &&
	    (hdev->tx_sch_mode != HCLGE_FLAG_VNET_BASE_SCH_MODE))
		return -ENOTSUPP;

	ret = hclge_tm_schd_setup_hw(hdev);
	if (ret)
		return ret;

	ret = hclge_pause_setup_hw(hdev, init);
	if (ret)
		return ret;

	return 0;
}