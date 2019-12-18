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
struct ib_udata {int dummy; } ;
struct ib_srq_attr {scalar_t__ srq_limit; } ;
struct ib_srq {int /*<<< orphan*/  device; } ;
struct hns_roce_srq_context {int /*<<< orphan*/  byte_8_limit_wl; } ;
struct hns_roce_srq {scalar_t__ max; int /*<<< orphan*/  srqn; } ;
struct hns_roce_dev {int /*<<< orphan*/  dev; } ;
struct hns_roce_cmd_mailbox {int /*<<< orphan*/  dma; struct hns_roce_srq_context* buf; } ;
typedef  enum ib_srq_attr_mask { ____Placeholder_ib_srq_attr_mask } ib_srq_attr_mask ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HNS_ROCE_CMD_MODIFY_SRQC ; 
 int /*<<< orphan*/  HNS_ROCE_CMD_TIMEOUT_MSECS ; 
 int IB_SRQ_LIMIT ; 
 scalar_t__ IS_ERR (struct hns_roce_cmd_mailbox*) ; 
 int PTR_ERR (struct hns_roce_cmd_mailbox*) ; 
 int /*<<< orphan*/  SRQC_BYTE_8_SRQ_LIMIT_WL_M ; 
 int /*<<< orphan*/  SRQC_BYTE_8_SRQ_LIMIT_WL_S ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct hns_roce_cmd_mailbox* hns_roce_alloc_cmd_mailbox (struct hns_roce_dev*) ; 
 int hns_roce_cmd_mbox (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_free_cmd_mailbox (struct hns_roce_dev*,struct hns_roce_cmd_mailbox*) ; 
 int /*<<< orphan*/  memset (struct hns_roce_srq_context*,int,int) ; 
 int /*<<< orphan*/  roce_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 struct hns_roce_srq* to_hr_srq (struct ib_srq*) ; 

__attribute__((used)) static int hns_roce_v2_modify_srq(struct ib_srq *ibsrq,
				  struct ib_srq_attr *srq_attr,
				  enum ib_srq_attr_mask srq_attr_mask,
				  struct ib_udata *udata)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(ibsrq->device);
	struct hns_roce_srq *srq = to_hr_srq(ibsrq);
	struct hns_roce_srq_context *srq_context;
	struct hns_roce_srq_context *srqc_mask;
	struct hns_roce_cmd_mailbox *mailbox;
	int ret;

	if (srq_attr_mask & IB_SRQ_LIMIT) {
		if (srq_attr->srq_limit >= srq->max)
			return -EINVAL;

		mailbox = hns_roce_alloc_cmd_mailbox(hr_dev);
		if (IS_ERR(mailbox))
			return PTR_ERR(mailbox);

		srq_context = mailbox->buf;
		srqc_mask = (struct hns_roce_srq_context *)mailbox->buf + 1;

		memset(srqc_mask, 0xff, sizeof(*srqc_mask));

		roce_set_field(srq_context->byte_8_limit_wl,
			       SRQC_BYTE_8_SRQ_LIMIT_WL_M,
			       SRQC_BYTE_8_SRQ_LIMIT_WL_S, srq_attr->srq_limit);
		roce_set_field(srqc_mask->byte_8_limit_wl,
			       SRQC_BYTE_8_SRQ_LIMIT_WL_M,
			       SRQC_BYTE_8_SRQ_LIMIT_WL_S, 0);

		ret = hns_roce_cmd_mbox(hr_dev, mailbox->dma, 0, srq->srqn, 0,
					HNS_ROCE_CMD_MODIFY_SRQC,
					HNS_ROCE_CMD_TIMEOUT_MSECS);
		hns_roce_free_cmd_mailbox(hr_dev, mailbox);
		if (ret) {
			dev_err(hr_dev->dev,
				"MODIFY SRQ Failed to cmd mailbox.\n");
			return ret;
		}
	}

	return 0;
}