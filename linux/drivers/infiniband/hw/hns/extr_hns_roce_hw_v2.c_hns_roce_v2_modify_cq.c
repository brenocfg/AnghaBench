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
typedef  int /*<<< orphan*/  u16 ;
struct ib_cq {int /*<<< orphan*/  device; } ;
struct hns_roce_v2_cq_context {int /*<<< orphan*/  byte_56_cqe_period_maxcnt; } ;
struct hns_roce_dev {int /*<<< orphan*/  dev; } ;
struct hns_roce_cq {int /*<<< orphan*/  cqn; } ;
struct hns_roce_cmd_mailbox {int /*<<< orphan*/  dma; struct hns_roce_v2_cq_context* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS_ROCE_CMD_MODIFY_CQC ; 
 int /*<<< orphan*/  HNS_ROCE_CMD_TIMEOUT_MSECS ; 
 scalar_t__ IS_ERR (struct hns_roce_cmd_mailbox*) ; 
 int PTR_ERR (struct hns_roce_cmd_mailbox*) ; 
 int /*<<< orphan*/  V2_CQC_BYTE_56_CQ_MAX_CNT_M ; 
 int /*<<< orphan*/  V2_CQC_BYTE_56_CQ_MAX_CNT_S ; 
 int /*<<< orphan*/  V2_CQC_BYTE_56_CQ_PERIOD_M ; 
 int /*<<< orphan*/  V2_CQC_BYTE_56_CQ_PERIOD_S ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct hns_roce_cmd_mailbox* hns_roce_alloc_cmd_mailbox (struct hns_roce_dev*) ; 
 int hns_roce_cmd_mbox (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_free_cmd_mailbox (struct hns_roce_dev*,struct hns_roce_cmd_mailbox*) ; 
 int /*<<< orphan*/  memset (struct hns_roce_v2_cq_context*,int,int) ; 
 int /*<<< orphan*/  roce_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hns_roce_cq* to_hr_cq (struct ib_cq*) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_roce_v2_modify_cq(struct ib_cq *cq, u16 cq_count, u16 cq_period)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(cq->device);
	struct hns_roce_v2_cq_context *cq_context;
	struct hns_roce_cq *hr_cq = to_hr_cq(cq);
	struct hns_roce_v2_cq_context *cqc_mask;
	struct hns_roce_cmd_mailbox *mailbox;
	int ret;

	mailbox = hns_roce_alloc_cmd_mailbox(hr_dev);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);

	cq_context = mailbox->buf;
	cqc_mask = (struct hns_roce_v2_cq_context *)mailbox->buf + 1;

	memset(cqc_mask, 0xff, sizeof(*cqc_mask));

	roce_set_field(cq_context->byte_56_cqe_period_maxcnt,
		       V2_CQC_BYTE_56_CQ_MAX_CNT_M, V2_CQC_BYTE_56_CQ_MAX_CNT_S,
		       cq_count);
	roce_set_field(cqc_mask->byte_56_cqe_period_maxcnt,
		       V2_CQC_BYTE_56_CQ_MAX_CNT_M, V2_CQC_BYTE_56_CQ_MAX_CNT_S,
		       0);
	roce_set_field(cq_context->byte_56_cqe_period_maxcnt,
		       V2_CQC_BYTE_56_CQ_PERIOD_M, V2_CQC_BYTE_56_CQ_PERIOD_S,
		       cq_period);
	roce_set_field(cqc_mask->byte_56_cqe_period_maxcnt,
		       V2_CQC_BYTE_56_CQ_PERIOD_M, V2_CQC_BYTE_56_CQ_PERIOD_S,
		       0);

	ret = hns_roce_cmd_mbox(hr_dev, mailbox->dma, 0, hr_cq->cqn, 1,
				HNS_ROCE_CMD_MODIFY_CQC,
				HNS_ROCE_CMD_TIMEOUT_MSECS);
	hns_roce_free_cmd_mailbox(hr_dev, mailbox);
	if (ret)
		dev_err(hr_dev->dev, "MODIFY CQ Failed to cmd mailbox.\n");

	return ret;
}