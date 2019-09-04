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
struct TYPE_2__ {int /*<<< orphan*/  reserved_cqs; scalar_t__ num_cqs; } ;
struct hns_roce_cq_table {int /*<<< orphan*/  bitmap; int /*<<< orphan*/  tree; int /*<<< orphan*/  lock; } ;
struct hns_roce_dev {TYPE_1__ caps; struct hns_roce_cq_table cq_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hns_roce_bitmap_init (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int hns_roce_init_cq_table(struct hns_roce_dev *hr_dev)
{
	struct hns_roce_cq_table *cq_table = &hr_dev->cq_table;

	spin_lock_init(&cq_table->lock);
	INIT_RADIX_TREE(&cq_table->tree, GFP_ATOMIC);

	return hns_roce_bitmap_init(&cq_table->bitmap, hr_dev->caps.num_cqs,
				    hr_dev->caps.num_cqs - 1,
				    hr_dev->caps.reserved_cqs, 0);
}