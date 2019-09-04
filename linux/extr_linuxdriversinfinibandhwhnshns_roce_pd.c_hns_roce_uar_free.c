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
struct hns_roce_uar {int /*<<< orphan*/  logic_idx; } ;
struct TYPE_2__ {int /*<<< orphan*/  bitmap; } ;
struct hns_roce_dev {TYPE_1__ uar_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_NO_RR ; 
 int /*<<< orphan*/  hns_roce_bitmap_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hns_roce_uar_free(struct hns_roce_dev *hr_dev, struct hns_roce_uar *uar)
{
	hns_roce_bitmap_free(&hr_dev->uar_table.bitmap, uar->logic_idx,
			     BITMAP_NO_RR);
}