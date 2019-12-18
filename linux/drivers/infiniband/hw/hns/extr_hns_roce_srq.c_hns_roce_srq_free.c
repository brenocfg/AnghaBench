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
struct hns_roce_srq_table {int /*<<< orphan*/  bitmap; int /*<<< orphan*/  table; int /*<<< orphan*/  xa; } ;
struct hns_roce_srq {int /*<<< orphan*/  srqn; int /*<<< orphan*/  free; int /*<<< orphan*/  refcount; } ;
struct hns_roce_dev {int /*<<< orphan*/  dev; struct hns_roce_srq_table srq_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_NO_RR ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_bitmap_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hns_roce_hw2sw_srq (struct hns_roce_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_table_put (struct hns_roce_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_roce_srq_free(struct hns_roce_dev *hr_dev,
			      struct hns_roce_srq *srq)
{
	struct hns_roce_srq_table *srq_table = &hr_dev->srq_table;
	int ret;

	ret = hns_roce_hw2sw_srq(hr_dev, NULL, srq->srqn);
	if (ret)
		dev_err(hr_dev->dev, "HW2SW_SRQ failed (%d) for CQN %06lx\n",
			ret, srq->srqn);

	xa_erase(&srq_table->xa, srq->srqn);

	if (atomic_dec_and_test(&srq->refcount))
		complete(&srq->free);
	wait_for_completion(&srq->free);

	hns_roce_table_put(hr_dev, &srq_table->table, srq->srqn);
	hns_roce_bitmap_free(&srq_table->bitmap, srq->srqn, BITMAP_NO_RR);
}