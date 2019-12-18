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
typedef  int u32 ;
struct hns_roce_hem_table {int dummy; } ;
struct hns_roce_buddy {int dummy; } ;
struct hns_roce_mr_table {struct hns_roce_hem_table mtt_idx_table; struct hns_roce_buddy mtt_idx_buddy; struct hns_roce_hem_table mtt_srqwqe_table; struct hns_roce_buddy mtt_srqwqe_buddy; struct hns_roce_hem_table mtt_cqe_table; struct hns_roce_buddy mtt_cqe_buddy; struct hns_roce_hem_table mtt_table; struct hns_roce_buddy mtt_buddy; } ;
struct hns_roce_dev {int /*<<< orphan*/  dev; struct hns_roce_mr_table mr_table; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MTT_TYPE_CQE 131 
#define  MTT_TYPE_IDX 130 
#define  MTT_TYPE_SRQWQE 129 
#define  MTT_TYPE_WQE 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
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

	switch (mtt_type) {
	case MTT_TYPE_WQE:
		buddy = &mr_table->mtt_buddy;
		table = &mr_table->mtt_table;
		break;
	case MTT_TYPE_CQE:
		buddy = &mr_table->mtt_cqe_buddy;
		table = &mr_table->mtt_cqe_table;
		break;
	case MTT_TYPE_SRQWQE:
		buddy = &mr_table->mtt_srqwqe_buddy;
		table = &mr_table->mtt_srqwqe_table;
		break;
	case MTT_TYPE_IDX:
		buddy = &mr_table->mtt_idx_buddy;
		table = &mr_table->mtt_idx_table;
		break;
	default:
		dev_err(hr_dev->dev, "Unsupport MTT table type: %d\n",
			mtt_type);
		return -EINVAL;
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