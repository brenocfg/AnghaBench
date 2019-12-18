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
struct ib_srq_attr {int srq_limit; int /*<<< orphan*/  max_sge; scalar_t__ max_wr; } ;
struct ib_srq {int /*<<< orphan*/  device; } ;
struct hns_roce_srq_context {int /*<<< orphan*/  byte_8_limit_wl; } ;
struct hns_roce_srq {int /*<<< orphan*/  max_gs; scalar_t__ max; int /*<<< orphan*/  srqn; } ;
struct hns_roce_dev {int /*<<< orphan*/  dev; } ;
struct hns_roce_cmd_mailbox {struct hns_roce_srq_context* buf; int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS_ROCE_CMD_QUERY_SRQC ; 
 int /*<<< orphan*/  HNS_ROCE_CMD_TIMEOUT_MSECS ; 
 scalar_t__ IS_ERR (struct hns_roce_cmd_mailbox*) ; 
 int PTR_ERR (struct hns_roce_cmd_mailbox*) ; 
 int /*<<< orphan*/  SRQC_BYTE_8_SRQ_LIMIT_WL_M ; 
 int /*<<< orphan*/  SRQC_BYTE_8_SRQ_LIMIT_WL_S ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct hns_roce_cmd_mailbox* hns_roce_alloc_cmd_mailbox (struct hns_roce_dev*) ; 
 int hns_roce_cmd_mbox (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_free_cmd_mailbox (struct hns_roce_dev*,struct hns_roce_cmd_mailbox*) ; 
 int /*<<< orphan*/  memcpy (struct hns_roce_srq_context*,struct hns_roce_srq_context*,int) ; 
 int roce_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 struct hns_roce_srq* to_hr_srq (struct ib_srq*) ; 

__attribute__((used)) static int hns_roce_v2_query_srq(struct ib_srq *ibsrq, struct ib_srq_attr *attr)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(ibsrq->device);
	struct hns_roce_srq *srq = to_hr_srq(ibsrq);
	struct hns_roce_srq_context *srq_context;
	struct hns_roce_cmd_mailbox *mailbox;
	int limit_wl;
	int ret;

	mailbox = hns_roce_alloc_cmd_mailbox(hr_dev);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);

	srq_context = mailbox->buf;
	ret = hns_roce_cmd_mbox(hr_dev, 0, mailbox->dma, srq->srqn, 0,
				HNS_ROCE_CMD_QUERY_SRQC,
				HNS_ROCE_CMD_TIMEOUT_MSECS);
	if (ret) {
		dev_err(hr_dev->dev, "QUERY SRQ cmd process error\n");
		goto out;
	}

	limit_wl = roce_get_field(srq_context->byte_8_limit_wl,
				  SRQC_BYTE_8_SRQ_LIMIT_WL_M,
				  SRQC_BYTE_8_SRQ_LIMIT_WL_S);

	attr->srq_limit = limit_wl;
	attr->max_wr    = srq->max - 1;
	attr->max_sge   = srq->max_gs;

	memcpy(srq_context, mailbox->buf, sizeof(*srq_context));

out:
	hns_roce_free_cmd_mailbox(hr_dev, mailbox);
	return ret;
}