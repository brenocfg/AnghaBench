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
struct TYPE_2__ {int /*<<< orphan*/  bitmap; } ;
struct hns_roce_dev {TYPE_1__ cq_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns_roce_bitmap_cleanup (int /*<<< orphan*/ *) ; 

void hns_roce_cleanup_cq_table(struct hns_roce_dev *hr_dev)
{
	hns_roce_bitmap_cleanup(&hr_dev->cq_table.bitmap);
}