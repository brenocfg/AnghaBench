#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct hns_roce_mtt {int /*<<< orphan*/  first_seg; } ;
struct hns_roce_hem_table {int dummy; } ;
struct TYPE_5__ {int num_comp_vectors; } ;
struct TYPE_4__ {struct hns_roce_hem_table mtt_table; struct hns_roce_hem_table mtt_cqe_table; } ;
struct hns_roce_cq_table {int /*<<< orphan*/  bitmap; int /*<<< orphan*/  table; int /*<<< orphan*/  array; } ;
struct hns_roce_dev {TYPE_3__* hw; TYPE_2__ caps; TYPE_1__ mr_table; struct hns_roce_cq_table cq_table; struct device* dev; } ;
struct hns_roce_cq {int vector; int arm_sn; int /*<<< orphan*/  cqn; int /*<<< orphan*/  free; int /*<<< orphan*/  refcount; scalar_t__ cons_index; } ;
struct hns_roce_cmd_mailbox {int /*<<< orphan*/  buf; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* write_cqc ) (struct hns_roce_dev*,struct hns_roce_cq*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_NO_RR ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HEM_TYPE_CQE ; 
 scalar_t__ IS_ERR (struct hns_roce_cmd_mailbox*) ; 
 int PTR_ERR (struct hns_roce_cmd_mailbox*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct hns_roce_cmd_mailbox* hns_roce_alloc_cmd_mailbox (struct hns_roce_dev*) ; 
 int hns_roce_bitmap_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_roce_bitmap_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hns_roce_check_whether_mhop (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_free_cmd_mailbox (struct hns_roce_dev*,struct hns_roce_cmd_mailbox*) ; 
 int hns_roce_sw2hw_cq (struct hns_roce_dev*,struct hns_roce_cmd_mailbox*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hns_roce_table_find (struct hns_roce_dev*,struct hns_roce_hem_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int hns_roce_table_get (struct hns_roce_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_table_put (struct hns_roce_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct hns_roce_dev*,struct hns_roce_cq*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  xa_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xa_err (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct hns_roce_cq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_roce_cq_alloc(struct hns_roce_dev *hr_dev, int nent,
			     struct hns_roce_mtt *hr_mtt,
			     struct hns_roce_cq *hr_cq, int vector)
{
	struct hns_roce_cmd_mailbox *mailbox;
	struct hns_roce_hem_table *mtt_table;
	struct hns_roce_cq_table *cq_table;
	struct device *dev = hr_dev->dev;
	dma_addr_t dma_handle;
	u64 *mtts;
	int ret;

	cq_table = &hr_dev->cq_table;

	/* Get the physical address of cq buf */
	if (hns_roce_check_whether_mhop(hr_dev, HEM_TYPE_CQE))
		mtt_table = &hr_dev->mr_table.mtt_cqe_table;
	else
		mtt_table = &hr_dev->mr_table.mtt_table;

	mtts = hns_roce_table_find(hr_dev, mtt_table,
				   hr_mtt->first_seg, &dma_handle);
	if (!mtts) {
		dev_err(dev, "CQ alloc.Failed to find cq buf addr.\n");
		return -EINVAL;
	}

	if (vector >= hr_dev->caps.num_comp_vectors) {
		dev_err(dev, "CQ alloc.Invalid vector.\n");
		return -EINVAL;
	}
	hr_cq->vector = vector;

	ret = hns_roce_bitmap_alloc(&cq_table->bitmap, &hr_cq->cqn);
	if (ret == -1) {
		dev_err(dev, "CQ alloc.Failed to alloc index.\n");
		return -ENOMEM;
	}

	/* Get CQC memory HEM(Hardware Entry Memory) table */
	ret = hns_roce_table_get(hr_dev, &cq_table->table, hr_cq->cqn);
	if (ret) {
		dev_err(dev, "CQ alloc.Failed to get context mem.\n");
		goto err_out;
	}

	ret = xa_err(xa_store(&cq_table->array, hr_cq->cqn, hr_cq, GFP_KERNEL));
	if (ret) {
		dev_err(dev, "CQ alloc failed xa_store.\n");
		goto err_put;
	}

	/* Allocate mailbox memory */
	mailbox = hns_roce_alloc_cmd_mailbox(hr_dev);
	if (IS_ERR(mailbox)) {
		ret = PTR_ERR(mailbox);
		goto err_xa;
	}

	hr_dev->hw->write_cqc(hr_dev, hr_cq, mailbox->buf, mtts, dma_handle,
			      nent, vector);

	/* Send mailbox to hw */
	ret = hns_roce_sw2hw_cq(hr_dev, mailbox, hr_cq->cqn);
	hns_roce_free_cmd_mailbox(hr_dev, mailbox);
	if (ret) {
		dev_err(dev, "CQ alloc.Failed to cmd mailbox.\n");
		goto err_xa;
	}

	hr_cq->cons_index = 0;
	hr_cq->arm_sn = 1;

	atomic_set(&hr_cq->refcount, 1);
	init_completion(&hr_cq->free);

	return 0;

err_xa:
	xa_erase(&cq_table->array, hr_cq->cqn);

err_put:
	hns_roce_table_put(hr_dev, &cq_table->table, hr_cq->cqn);

err_out:
	hns_roce_bitmap_free(&cq_table->bitmap, hr_cq->cqn, BITMAP_NO_RR);
	return ret;
}