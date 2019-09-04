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
struct TYPE_2__ {int hw_pfc_map; } ;
struct hclge_dev {int hw_tc_map; TYPE_1__ tm_info; } ;

/* Variables and functions */
 int BIT (int) ; 
 int HCLGE_MAX_TC_NUM ; 

__attribute__((used)) static int hclge_get_pfc_enalbe_num(struct hclge_dev *hdev)
{
	int i, cnt = 0;

	for (i = 0; i < HCLGE_MAX_TC_NUM; i++)
		if (hdev->hw_tc_map & BIT(i) &&
		    hdev->tm_info.hw_pfc_map & BIT(i))
			cnt++;
	return cnt;
}