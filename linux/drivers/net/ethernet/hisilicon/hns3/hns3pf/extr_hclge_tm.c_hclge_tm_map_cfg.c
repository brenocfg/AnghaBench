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
 int hclge_tm_pg_to_pri_map (struct hclge_dev*) ; 
 int hclge_tm_pri_q_qs_cfg (struct hclge_dev*) ; 
 int hclge_up_to_tc_map (struct hclge_dev*) ; 

__attribute__((used)) static int hclge_tm_map_cfg(struct hclge_dev *hdev)
{
	int ret;

	ret = hclge_up_to_tc_map(hdev);
	if (ret)
		return ret;

	ret = hclge_tm_pg_to_pri_map(hdev);
	if (ret)
		return ret;

	return hclge_tm_pri_q_qs_cfg(hdev);
}