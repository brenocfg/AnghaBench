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
struct hclge_dev {int dummy; } ;

/* Variables and functions */
 int hclge_tm_dwrr_cfg (struct hclge_dev*) ; 
 int hclge_tm_map_cfg (struct hclge_dev*) ; 
 int hclge_tm_schd_mode_hw (struct hclge_dev*) ; 
 int hclge_tm_shaper_cfg (struct hclge_dev*) ; 

int hclge_tm_schd_setup_hw(struct hclge_dev *hdev)
{
	int ret;

	/* Cfg tm mapping  */
	ret = hclge_tm_map_cfg(hdev);
	if (ret)
		return ret;

	/* Cfg tm shaper */
	ret = hclge_tm_shaper_cfg(hdev);
	if (ret)
		return ret;

	/* Cfg dwrr */
	ret = hclge_tm_dwrr_cfg(hdev);
	if (ret)
		return ret;

	/* Cfg schd mode for each level schd */
	return hclge_tm_schd_mode_hw(hdev);
}