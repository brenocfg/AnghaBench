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
struct mthca_tavor_srq_context {int /*<<< orphan*/  limit_watermark; } ;
struct mthca_srq {int /*<<< orphan*/  max_gs; scalar_t__ max; int /*<<< orphan*/  srqn; } ;
struct mthca_mailbox {struct mthca_tavor_srq_context* buf; } ;
struct mthca_dev {int dummy; } ;
struct mthca_arbel_srq_context {int /*<<< orphan*/  limit_watermark; } ;
struct ib_srq_attr {int /*<<< orphan*/  max_sge; scalar_t__ max_wr; void* srq_limit; } ;
struct ib_srq {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mthca_mailbox*) ; 
 int PTR_ERR (struct mthca_mailbox*) ; 
 void* be16_to_cpu (int /*<<< orphan*/ ) ; 
 int mthca_QUERY_SRQ (struct mthca_dev*,int /*<<< orphan*/ ,struct mthca_mailbox*) ; 
 struct mthca_mailbox* mthca_alloc_mailbox (struct mthca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_free_mailbox (struct mthca_dev*,struct mthca_mailbox*) ; 
 scalar_t__ mthca_is_memfree (struct mthca_dev*) ; 
 struct mthca_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mthca_srq* to_msrq (struct ib_srq*) ; 

int mthca_query_srq(struct ib_srq *ibsrq, struct ib_srq_attr *srq_attr)
{
	struct mthca_dev *dev = to_mdev(ibsrq->device);
	struct mthca_srq *srq = to_msrq(ibsrq);
	struct mthca_mailbox *mailbox;
	struct mthca_arbel_srq_context *arbel_ctx;
	struct mthca_tavor_srq_context *tavor_ctx;
	int err;

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);

	err = mthca_QUERY_SRQ(dev, srq->srqn, mailbox);
	if (err)
		goto out;

	if (mthca_is_memfree(dev)) {
		arbel_ctx = mailbox->buf;
		srq_attr->srq_limit = be16_to_cpu(arbel_ctx->limit_watermark);
	} else {
		tavor_ctx = mailbox->buf;
		srq_attr->srq_limit = be16_to_cpu(tavor_ctx->limit_watermark);
	}

	srq_attr->max_wr  = srq->max - 1;
	srq_attr->max_sge = srq->max_gs;

out:
	mthca_free_mailbox(dev, mailbox);

	return err;
}