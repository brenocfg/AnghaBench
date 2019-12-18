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
 int hclge_tm_lvl2_schd_mode_cfg (struct hclge_dev*) ; 
 int hclge_tm_lvl34_schd_mode_cfg (struct hclge_dev*) ; 

__attribute__((used)) static int hclge_tm_schd_mode_hw(struct hclge_dev *hdev)
{
	int ret;

	ret = hclge_tm_lvl2_schd_mode_cfg(hdev);
	if (ret)
		return ret;

	return hclge_tm_lvl34_schd_mode_cfg(hdev);
}