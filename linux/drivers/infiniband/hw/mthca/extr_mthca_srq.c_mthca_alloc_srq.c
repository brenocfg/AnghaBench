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
struct mthca_srq {scalar_t__ max; int max_gs; int srqn; scalar_t__ db_index; int refcount; int last_free; scalar_t__ first_free; int /*<<< orphan*/  mutex; int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; int /*<<< orphan*/  db; int /*<<< orphan*/  wqe_shift; scalar_t__ counter; } ;
struct mthca_pd {int dummy; } ;
struct mthca_next_seg {int dummy; } ;
struct mthca_mailbox {int /*<<< orphan*/  buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  alloc; int /*<<< orphan*/  table; int /*<<< orphan*/  lock; int /*<<< orphan*/  srq; } ;
struct TYPE_3__ {scalar_t__ max_srq_wqes; int max_srq_sge; int max_desc_sz; int num_srqs; } ;
struct mthca_dev {TYPE_2__ srq_table; TYPE_1__ limits; } ;
struct mthca_data_seg {int dummy; } ;
struct ib_udata {int dummy; } ;
struct ib_srq_attr {scalar_t__ max_wr; int max_sge; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mthca_mailbox*) ; 
 int /*<<< orphan*/  MTHCA_DB_TYPE_SRQ ; 
 int PTR_ERR (struct mthca_mailbox*) ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int max (unsigned long,scalar_t__) ; 
 int mthca_HW2SW_SRQ (struct mthca_dev*,struct mthca_mailbox*,int) ; 
 int mthca_SW2HW_SRQ (struct mthca_dev*,struct mthca_mailbox*,int) ; 
 int mthca_alloc (int /*<<< orphan*/ *) ; 
 scalar_t__ mthca_alloc_db (struct mthca_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct mthca_mailbox* mthca_alloc_mailbox (struct mthca_dev*,int /*<<< orphan*/ ) ; 
 int mthca_alloc_srq_buf (struct mthca_dev*,struct mthca_pd*,struct mthca_srq*,struct ib_udata*) ; 
 int /*<<< orphan*/  mthca_arbel_init_srq_context (struct mthca_dev*,struct mthca_pd*,struct mthca_srq*,int /*<<< orphan*/ ,struct ib_udata*) ; 
 scalar_t__ mthca_array_set (int /*<<< orphan*/ *,int,struct mthca_srq*) ; 
 int /*<<< orphan*/  mthca_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mthca_free_db (struct mthca_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mthca_free_mailbox (struct mthca_dev*,struct mthca_mailbox*) ; 
 int /*<<< orphan*/  mthca_free_srq_buf (struct mthca_dev*,struct mthca_srq*) ; 
 scalar_t__ mthca_is_memfree (struct mthca_dev*) ; 
 int mthca_table_get (struct mthca_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mthca_table_put (struct mthca_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mthca_tavor_init_srq_context (struct mthca_dev*,struct mthca_pd*,struct mthca_srq*,int /*<<< orphan*/ ,struct ib_udata*) ; 
 int /*<<< orphan*/  mthca_warn (struct mthca_dev*,char*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ roundup_pow_of_two (int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int mthca_alloc_srq(struct mthca_dev *dev, struct mthca_pd *pd,
		    struct ib_srq_attr *attr, struct mthca_srq *srq,
		    struct ib_udata *udata)
{
	struct mthca_mailbox *mailbox;
	int ds;
	int err;

	/* Sanity check SRQ size before proceeding */
	if (attr->max_wr  > dev->limits.max_srq_wqes ||
	    attr->max_sge > dev->limits.max_srq_sge)
		return -EINVAL;

	srq->max      = attr->max_wr;
	srq->max_gs   = attr->max_sge;
	srq->counter  = 0;

	if (mthca_is_memfree(dev))
		srq->max = roundup_pow_of_two(srq->max + 1);
	else
		srq->max = srq->max + 1;

	ds = max(64UL,
		 roundup_pow_of_two(sizeof (struct mthca_next_seg) +
				    srq->max_gs * sizeof (struct mthca_data_seg)));

	if (!mthca_is_memfree(dev) && (ds > dev->limits.max_desc_sz))
		return -EINVAL;

	srq->wqe_shift = ilog2(ds);

	srq->srqn = mthca_alloc(&dev->srq_table.alloc);
	if (srq->srqn == -1)
		return -ENOMEM;

	if (mthca_is_memfree(dev)) {
		err = mthca_table_get(dev, dev->srq_table.table, srq->srqn);
		if (err)
			goto err_out;

		if (!udata) {
			srq->db_index = mthca_alloc_db(dev, MTHCA_DB_TYPE_SRQ,
						       srq->srqn, &srq->db);
			if (srq->db_index < 0) {
				err = -ENOMEM;
				goto err_out_icm;
			}
		}
	}

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	if (IS_ERR(mailbox)) {
		err = PTR_ERR(mailbox);
		goto err_out_db;
	}

	err = mthca_alloc_srq_buf(dev, pd, srq, udata);
	if (err)
		goto err_out_mailbox;

	spin_lock_init(&srq->lock);
	srq->refcount = 1;
	init_waitqueue_head(&srq->wait);
	mutex_init(&srq->mutex);

	if (mthca_is_memfree(dev))
		mthca_arbel_init_srq_context(dev, pd, srq, mailbox->buf, udata);
	else
		mthca_tavor_init_srq_context(dev, pd, srq, mailbox->buf, udata);

	err = mthca_SW2HW_SRQ(dev, mailbox, srq->srqn);

	if (err) {
		mthca_warn(dev, "SW2HW_SRQ failed (%d)\n", err);
		goto err_out_free_buf;
	}

	spin_lock_irq(&dev->srq_table.lock);
	if (mthca_array_set(&dev->srq_table.srq,
			    srq->srqn & (dev->limits.num_srqs - 1),
			    srq)) {
		spin_unlock_irq(&dev->srq_table.lock);
		goto err_out_free_srq;
	}
	spin_unlock_irq(&dev->srq_table.lock);

	mthca_free_mailbox(dev, mailbox);

	srq->first_free = 0;
	srq->last_free  = srq->max - 1;

	attr->max_wr    = srq->max - 1;
	attr->max_sge   = srq->max_gs;

	return 0;

err_out_free_srq:
	err = mthca_HW2SW_SRQ(dev, mailbox, srq->srqn);
	if (err)
		mthca_warn(dev, "HW2SW_SRQ failed (%d)\n", err);

err_out_free_buf:
	if (!udata)
		mthca_free_srq_buf(dev, srq);

err_out_mailbox:
	mthca_free_mailbox(dev, mailbox);

err_out_db:
	if (!udata && mthca_is_memfree(dev))
		mthca_free_db(dev, MTHCA_DB_TYPE_SRQ, srq->db_index);

err_out_icm:
	mthca_table_put(dev, dev->srq_table.table, srq->srqn);

err_out:
	mthca_free(&dev->srq_table.alloc, srq->srqn);

	return err;
}