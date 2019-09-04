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
struct hns_roce_qp_table {int /*<<< orphan*/  bitmap; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {scalar_t__ num_qps; } ;
struct hns_roce_dev {int /*<<< orphan*/  dev; TYPE_1__ caps; int /*<<< orphan*/  qp_table_tree; struct hns_roce_qp_table qp_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SQP_NUM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int hns_roce_bitmap_init (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int hns_roce_init_qp_table(struct hns_roce_dev *hr_dev)
{
	struct hns_roce_qp_table *qp_table = &hr_dev->qp_table;
	int reserved_from_top = 0;
	int ret;

	spin_lock_init(&qp_table->lock);
	INIT_RADIX_TREE(&hr_dev->qp_table_tree, GFP_ATOMIC);

	/* A port include two SQP, six port total 12 */
	ret = hns_roce_bitmap_init(&qp_table->bitmap, hr_dev->caps.num_qps,
				   hr_dev->caps.num_qps - 1, SQP_NUM,
				   reserved_from_top);
	if (ret) {
		dev_err(hr_dev->dev, "qp bitmap init failed!error=%d\n",
			ret);
		return ret;
	}

	return 0;
}