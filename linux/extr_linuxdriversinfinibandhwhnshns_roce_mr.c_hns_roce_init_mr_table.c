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
struct hns_roce_mr_table {int /*<<< orphan*/  mtpt_bitmap; int /*<<< orphan*/  mtt_buddy; int /*<<< orphan*/  mtt_cqe_buddy; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_cqe_segs; int /*<<< orphan*/  num_mtt_segs; int /*<<< orphan*/  reserved_mrws; scalar_t__ num_mtpts; } ;
struct hns_roce_dev {TYPE_1__ caps; struct hns_roce_mr_table mr_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEM_TYPE_CQE ; 
 int /*<<< orphan*/  hns_roce_bitmap_cleanup (int /*<<< orphan*/ *) ; 
 int hns_roce_bitmap_init (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_buddy_cleanup (int /*<<< orphan*/ *) ; 
 int hns_roce_buddy_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hns_roce_check_whether_mhop (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilog2 (int /*<<< orphan*/ ) ; 

int hns_roce_init_mr_table(struct hns_roce_dev *hr_dev)
{
	struct hns_roce_mr_table *mr_table = &hr_dev->mr_table;
	int ret;

	ret = hns_roce_bitmap_init(&mr_table->mtpt_bitmap,
				   hr_dev->caps.num_mtpts,
				   hr_dev->caps.num_mtpts - 1,
				   hr_dev->caps.reserved_mrws, 0);
	if (ret)
		return ret;

	ret = hns_roce_buddy_init(&mr_table->mtt_buddy,
				  ilog2(hr_dev->caps.num_mtt_segs));
	if (ret)
		goto err_buddy;

	if (hns_roce_check_whether_mhop(hr_dev, HEM_TYPE_CQE)) {
		ret = hns_roce_buddy_init(&mr_table->mtt_cqe_buddy,
					  ilog2(hr_dev->caps.num_cqe_segs));
		if (ret)
			goto err_buddy_cqe;
	}
	return 0;

err_buddy_cqe:
	hns_roce_buddy_cleanup(&mr_table->mtt_buddy);

err_buddy:
	hns_roce_bitmap_cleanup(&mr_table->mtpt_bitmap);
	return ret;
}