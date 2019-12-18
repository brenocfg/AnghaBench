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
struct hns_roce_qp_table {int /*<<< orphan*/  bitmap; } ;
struct TYPE_2__ {int reserved_qps; } ;
struct hns_roce_dev {TYPE_1__ caps; struct hns_roce_qp_table qp_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_RR ; 
 int /*<<< orphan*/  hns_roce_bitmap_free_range (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

void hns_roce_release_range_qp(struct hns_roce_dev *hr_dev, int base_qpn,
			       int cnt)
{
	struct hns_roce_qp_table *qp_table = &hr_dev->qp_table;

	if (base_qpn < hr_dev->caps.reserved_qps)
		return;

	hns_roce_bitmap_free_range(&qp_table->bitmap, base_qpn, cnt, BITMAP_RR);
}