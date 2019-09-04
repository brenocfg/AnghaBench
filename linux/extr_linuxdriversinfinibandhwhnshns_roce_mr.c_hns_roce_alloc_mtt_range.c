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
typedef  scalar_t__ u32 ;
struct hns_roce_hem_table {int dummy; } ;
struct hns_roce_buddy {int dummy; } ;
struct hns_roce_mr_table {struct hns_roce_hem_table mtt_cqe_table; struct hns_roce_buddy mtt_cqe_buddy; struct hns_roce_hem_table mtt_table; struct hns_roce_buddy mtt_buddy; } ;
struct hns_roce_dev {struct hns_roce_mr_table mr_table; } ;

/* Variables and functions */
 scalar_t__ MTT_TYPE_WQE ; 
 int hns_roce_buddy_alloc (struct hns_roce_buddy*,int,unsigned long*) ; 
 int /*<<< orphan*/  hns_roce_buddy_free (struct hns_roce_buddy*,unsigned long,int) ; 
 scalar_t__ hns_roce_table_get_range (struct hns_roce_dev*,struct hns_roce_hem_table*,unsigned long,unsigned long) ; 

__attribute__((used)) static int hns_roce_alloc_mtt_range(struct hns_roce_dev *hr_dev, int order,
				    unsigned long *seg, u32 mtt_type)
{
	struct hns_roce_mr_table *mr_table = &hr_dev->mr_table;
	struct hns_roce_hem_table *table;
	struct hns_roce_buddy *buddy;
	int ret;

	if (mtt_type == MTT_TYPE_WQE) {
		buddy = &mr_table->mtt_buddy;
		table = &mr_table->mtt_table;
	} else {
		buddy = &mr_table->mtt_cqe_buddy;
		table = &mr_table->mtt_cqe_table;
	}

	ret = hns_roce_buddy_alloc(buddy, order, seg);
	if (ret == -1)
		return -1;

	if (hns_roce_table_get_range(hr_dev, table, *seg,
				     *seg + (1 << order) - 1)) {
		hns_roce_buddy_free(buddy, *seg, order);
		return -1;
	}

	return 0;
}