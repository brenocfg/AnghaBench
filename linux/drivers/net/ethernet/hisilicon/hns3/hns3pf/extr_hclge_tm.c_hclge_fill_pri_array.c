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
typedef  size_t u8 ;
struct TYPE_2__ {size_t* prio_tc; size_t num_tc; } ;
struct hclge_dev {TYPE_1__ tm_info; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int hclge_fill_pri_array(struct hclge_dev *hdev, u8 *pri, u8 pri_id)
{
	u8 tc;

	tc = hdev->tm_info.prio_tc[pri_id];

	if (tc >= hdev->tm_info.num_tc)
		return -EINVAL;

	/**
	 * the register for priority has four bytes, the first bytes includes
	 *  priority0 and priority1, the higher 4bit stands for priority1
	 *  while the lower 4bit stands for priority0, as below:
	 * first byte:	| pri_1 | pri_0 |
	 * second byte:	| pri_3 | pri_2 |
	 * third byte:	| pri_5 | pri_4 |
	 * fourth byte:	| pri_7 | pri_6 |
	 */
	pri[pri_id >> 1] |= tc << ((pri_id & 1) * 4);

	return 0;
}