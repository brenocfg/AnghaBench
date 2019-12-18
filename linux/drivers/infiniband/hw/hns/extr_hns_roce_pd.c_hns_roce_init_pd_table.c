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
struct TYPE_2__ {int /*<<< orphan*/  reserved_pds; scalar_t__ num_pds; } ;
struct hns_roce_dev {TYPE_1__ caps; int /*<<< orphan*/  pd_bitmap; } ;

/* Variables and functions */
 int hns_roce_bitmap_init (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hns_roce_init_pd_table(struct hns_roce_dev *hr_dev)
{
	return hns_roce_bitmap_init(&hr_dev->pd_bitmap, hr_dev->caps.num_pds,
				    hr_dev->caps.num_pds - 1,
				    hr_dev->caps.reserved_pds, 0);
}