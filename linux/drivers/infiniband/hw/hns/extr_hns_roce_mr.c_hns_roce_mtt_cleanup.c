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
struct hns_roce_mtt {scalar_t__ order; int mtt_type; int /*<<< orphan*/  first_seg; } ;
struct hns_roce_mr_table {int /*<<< orphan*/  mtt_idx_table; int /*<<< orphan*/  mtt_idx_buddy; int /*<<< orphan*/  mtt_srqwqe_table; int /*<<< orphan*/  mtt_srqwqe_buddy; int /*<<< orphan*/  mtt_cqe_table; int /*<<< orphan*/  mtt_cqe_buddy; int /*<<< orphan*/  mtt_table; int /*<<< orphan*/  mtt_buddy; } ;
struct hns_roce_dev {int /*<<< orphan*/  dev; struct hns_roce_mr_table mr_table; } ;

/* Variables and functions */
#define  MTT_TYPE_CQE 131 
#define  MTT_TYPE_IDX 130 
#define  MTT_TYPE_SRQWQE 129 
#define  MTT_TYPE_WQE 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hns_roce_buddy_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hns_roce_table_put_range (struct hns_roce_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hns_roce_mtt_cleanup(struct hns_roce_dev *hr_dev, struct hns_roce_mtt *mtt)
{
	struct hns_roce_mr_table *mr_table = &hr_dev->mr_table;

	if (mtt->order < 0)
		return;

	switch (mtt->mtt_type) {
	case MTT_TYPE_WQE:
		hns_roce_buddy_free(&mr_table->mtt_buddy, mtt->first_seg,
				    mtt->order);
		hns_roce_table_put_range(hr_dev, &mr_table->mtt_table,
					mtt->first_seg,
					mtt->first_seg + (1 << mtt->order) - 1);
		break;
	case MTT_TYPE_CQE:
		hns_roce_buddy_free(&mr_table->mtt_cqe_buddy, mtt->first_seg,
				    mtt->order);
		hns_roce_table_put_range(hr_dev, &mr_table->mtt_cqe_table,
					mtt->first_seg,
					mtt->first_seg + (1 << mtt->order) - 1);
		break;
	case MTT_TYPE_SRQWQE:
		hns_roce_buddy_free(&mr_table->mtt_srqwqe_buddy, mtt->first_seg,
				    mtt->order);
		hns_roce_table_put_range(hr_dev, &mr_table->mtt_srqwqe_table,
					mtt->first_seg,
					mtt->first_seg + (1 << mtt->order) - 1);
		break;
	case MTT_TYPE_IDX:
		hns_roce_buddy_free(&mr_table->mtt_idx_buddy, mtt->first_seg,
				    mtt->order);
		hns_roce_table_put_range(hr_dev, &mr_table->mtt_idx_table,
					mtt->first_seg,
					mtt->first_seg + (1 << mtt->order) - 1);
		break;
	default:
		dev_err(hr_dev->dev,
			"Unsupport mtt type %d, clean mtt failed\n",
			mtt->mtt_type);
		break;
	}
}