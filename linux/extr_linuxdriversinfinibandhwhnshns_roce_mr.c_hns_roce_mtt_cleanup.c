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
struct hns_roce_mtt {int order; scalar_t__ mtt_type; scalar_t__ first_seg; } ;
struct hns_roce_mr_table {int /*<<< orphan*/  mtt_cqe_table; int /*<<< orphan*/  mtt_cqe_buddy; int /*<<< orphan*/  mtt_table; int /*<<< orphan*/  mtt_buddy; } ;
struct hns_roce_dev {struct hns_roce_mr_table mr_table; } ;

/* Variables and functions */
 scalar_t__ MTT_TYPE_WQE ; 
 int /*<<< orphan*/  hns_roce_buddy_free (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  hns_roce_table_put_range (struct hns_roce_dev*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

void hns_roce_mtt_cleanup(struct hns_roce_dev *hr_dev, struct hns_roce_mtt *mtt)
{
	struct hns_roce_mr_table *mr_table = &hr_dev->mr_table;

	if (mtt->order < 0)
		return;

	if (mtt->mtt_type == MTT_TYPE_WQE) {
		hns_roce_buddy_free(&mr_table->mtt_buddy, mtt->first_seg,
				    mtt->order);
		hns_roce_table_put_range(hr_dev, &mr_table->mtt_table,
					mtt->first_seg,
					mtt->first_seg + (1 << mtt->order) - 1);
	} else {
		hns_roce_buddy_free(&mr_table->mtt_cqe_buddy, mtt->first_seg,
				    mtt->order);
		hns_roce_table_put_range(hr_dev, &mr_table->mtt_cqe_table,
					mtt->first_seg,
					mtt->first_seg + (1 << mtt->order) - 1);
	}
}