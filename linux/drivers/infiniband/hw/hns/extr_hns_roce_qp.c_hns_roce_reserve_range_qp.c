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
struct hns_roce_qp_table {int /*<<< orphan*/  bitmap; } ;
struct hns_roce_dev {struct hns_roce_qp_table qp_table; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ hns_roce_bitmap_alloc_range (int /*<<< orphan*/ *,int,int,unsigned long*) ; 

__attribute__((used)) static int hns_roce_reserve_range_qp(struct hns_roce_dev *hr_dev, int cnt,
				     int align, unsigned long *base)
{
	struct hns_roce_qp_table *qp_table = &hr_dev->qp_table;

	return hns_roce_bitmap_alloc_range(&qp_table->bitmap, cnt, align,
					   base) ?
		       -ENOMEM :
		       0;
}