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
typedef  scalar_t__ u32 ;
struct hclge_dev {int hw_tc_map; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 unsigned int HCLGE_MAX_TC_NUM ; 

__attribute__((used)) static u32 hclge_get_tc_num(struct hclge_dev *hdev)
{
	unsigned int i;
	u32 cnt = 0;

	for (i = 0; i < HCLGE_MAX_TC_NUM; i++)
		if (hdev->hw_tc_map & BIT(i))
			cnt++;
	return cnt;
}