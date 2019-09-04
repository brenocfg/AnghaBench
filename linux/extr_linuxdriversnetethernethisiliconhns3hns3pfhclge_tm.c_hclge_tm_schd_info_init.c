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
struct TYPE_2__ {int num_pg; } ;
struct hclge_dev {scalar_t__ tx_sch_mode; TYPE_1__ tm_info; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HCLGE_FLAG_TC_BASE_SCH_MODE ; 
 int /*<<< orphan*/  hclge_pfc_info_init (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_tm_pg_info_init (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_tm_tc_info_init (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_tm_vport_info_update (struct hclge_dev*) ; 

__attribute__((used)) static int hclge_tm_schd_info_init(struct hclge_dev *hdev)
{
	if ((hdev->tx_sch_mode != HCLGE_FLAG_TC_BASE_SCH_MODE) &&
	    (hdev->tm_info.num_pg != 1))
		return -EINVAL;

	hclge_tm_pg_info_init(hdev);

	hclge_tm_tc_info_init(hdev);

	hclge_tm_vport_info_update(hdev);

	hclge_pfc_info_init(hdev);

	return 0;
}