#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_6__ {size_t num_tc; size_t* prio_tc; TYPE_2__* pg_info; TYPE_1__* tc_info; } ;
struct hclge_dev {int /*<<< orphan*/  flag; TYPE_3__ tm_info; } ;
struct TYPE_5__ {int /*<<< orphan*/  bw_limit; } ;
struct TYPE_4__ {size_t tc_id; int /*<<< orphan*/  bw_limit; scalar_t__ pgid; int /*<<< orphan*/  tc_sch_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_FLAG_DCB_ENABLE ; 
 int /*<<< orphan*/  HCLGE_SCH_MODE_DWRR ; 
 size_t HNAE3_MAX_USER_PRIO ; 

__attribute__((used)) static void hclge_tm_tc_info_init(struct hclge_dev *hdev)
{
	u8 i;

	for (i = 0; i < hdev->tm_info.num_tc; i++) {
		hdev->tm_info.tc_info[i].tc_id = i;
		hdev->tm_info.tc_info[i].tc_sch_mode = HCLGE_SCH_MODE_DWRR;
		hdev->tm_info.tc_info[i].pgid = 0;
		hdev->tm_info.tc_info[i].bw_limit =
			hdev->tm_info.pg_info[0].bw_limit;
	}

	for (i = 0; i < HNAE3_MAX_USER_PRIO; i++)
		hdev->tm_info.prio_tc[i] =
			(i >= hdev->tm_info.num_tc) ? 0 : i;

	/* DCB is enabled if we have more than 1 TC */
	if (hdev->tm_info.num_tc > 1)
		hdev->flag |= HCLGE_FLAG_DCB_ENABLE;
	else
		hdev->flag &= ~HCLGE_FLAG_DCB_ENABLE;
}