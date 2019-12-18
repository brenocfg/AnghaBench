#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* eq; } ;
struct hns_roce_cq_table {int /*<<< orphan*/  bitmap; int /*<<< orphan*/  table; int /*<<< orphan*/  array; } ;
struct hns_roce_dev {TYPE_2__ eq_table; struct device* dev; struct hns_roce_cq_table cq_table; } ;
struct hns_roce_cq {size_t vector; int /*<<< orphan*/  cqn; int /*<<< orphan*/  free; int /*<<< orphan*/  refcount; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_NO_RR ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_bitmap_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hns_roce_hw2sw_cq (struct hns_roce_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_table_put (struct hns_roce_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void hns_roce_free_cq(struct hns_roce_dev *hr_dev, struct hns_roce_cq *hr_cq)
{
	struct hns_roce_cq_table *cq_table = &hr_dev->cq_table;
	struct device *dev = hr_dev->dev;
	int ret;

	ret = hns_roce_hw2sw_cq(hr_dev, NULL, hr_cq->cqn);
	if (ret)
		dev_err(dev, "HW2SW_CQ failed (%d) for CQN %06lx\n", ret,
			hr_cq->cqn);

	xa_erase(&cq_table->array, hr_cq->cqn);

	/* Waiting interrupt process procedure carried out */
	synchronize_irq(hr_dev->eq_table.eq[hr_cq->vector].irq);

	/* wait for all interrupt processed */
	if (atomic_dec_and_test(&hr_cq->refcount))
		complete(&hr_cq->free);
	wait_for_completion(&hr_cq->free);

	hns_roce_table_put(hr_dev, &cq_table->table, hr_cq->cqn);
	hns_roce_bitmap_free(&cq_table->bitmap, hr_cq->cqn, BITMAP_NO_RR);
}