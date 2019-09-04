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
typedef  size_t u8 ;
struct TYPE_4__ {size_t num_pg; int* pg_dwrr; int num_tc; TYPE_1__* pg_info; } ;
struct hclge_dev {TYPE_2__ tm_info; int /*<<< orphan*/  hw_tc_map; } ;
struct TYPE_3__ {size_t pg_id; int* tc_dwrr; int /*<<< orphan*/  tc_bit_map; int /*<<< orphan*/  bw_limit; int /*<<< orphan*/  pg_sch_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_ETHER_MAX_RATE ; 
 int /*<<< orphan*/  HCLGE_SCH_MODE_DWRR ; 

__attribute__((used)) static void hclge_tm_pg_info_init(struct hclge_dev *hdev)
{
	u8 i;

	for (i = 0; i < hdev->tm_info.num_pg; i++) {
		int k;

		hdev->tm_info.pg_dwrr[i] = i ? 0 : 100;

		hdev->tm_info.pg_info[i].pg_id = i;
		hdev->tm_info.pg_info[i].pg_sch_mode = HCLGE_SCH_MODE_DWRR;

		hdev->tm_info.pg_info[i].bw_limit = HCLGE_ETHER_MAX_RATE;

		if (i != 0)
			continue;

		hdev->tm_info.pg_info[i].tc_bit_map = hdev->hw_tc_map;
		for (k = 0; k < hdev->tm_info.num_tc; k++)
			hdev->tm_info.pg_info[i].tc_dwrr[k] = 100;
	}
}