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
struct TYPE_4__ {int /*<<< orphan*/  reserved_uars; scalar_t__ num_uars; } ;
struct TYPE_3__ {int /*<<< orphan*/  bitmap; } ;
struct hns_roce_dev {TYPE_2__ caps; TYPE_1__ uar_table; } ;

/* Variables and functions */
 int hns_roce_bitmap_init (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hns_roce_init_uar_table(struct hns_roce_dev *hr_dev)
{
	return hns_roce_bitmap_init(&hr_dev->uar_table.bitmap,
				    hr_dev->caps.num_uars,
				    hr_dev->caps.num_uars - 1,
				    hr_dev->caps.reserved_uars, 0);
}