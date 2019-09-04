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
struct hns_roce_dev {int /*<<< orphan*/  pd_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns_roce_bitmap_cleanup (int /*<<< orphan*/ *) ; 

void hns_roce_cleanup_pd_table(struct hns_roce_dev *hr_dev)
{
	hns_roce_bitmap_cleanup(&hr_dev->pd_bitmap);
}