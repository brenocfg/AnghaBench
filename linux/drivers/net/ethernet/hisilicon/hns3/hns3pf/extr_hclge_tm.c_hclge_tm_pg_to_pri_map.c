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
typedef  size_t u32 ;
struct TYPE_4__ {size_t num_pg; TYPE_1__* pg_info; } ;
struct hclge_dev {scalar_t__ tx_sch_mode; TYPE_2__ tm_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  tc_bit_map; } ;

/* Variables and functions */
 scalar_t__ HCLGE_FLAG_TC_BASE_SCH_MODE ; 
 int hclge_tm_pg_to_pri_map_cfg (struct hclge_dev*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_tm_pg_to_pri_map(struct hclge_dev *hdev)
{
	int ret;
	u32 i;

	if (hdev->tx_sch_mode != HCLGE_FLAG_TC_BASE_SCH_MODE)
		return 0;

	for (i = 0; i < hdev->tm_info.num_pg; i++) {
		/* Cfg mapping */
		ret = hclge_tm_pg_to_pri_map_cfg(
			hdev, i, hdev->tm_info.pg_info[i].tc_bit_map);
		if (ret)
			return ret;
	}

	return 0;
}