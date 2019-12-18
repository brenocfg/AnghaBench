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
typedef  int /*<<< orphan*/  u32 ;
struct hns_roce_v2_cq_context {int dummy; } ;
struct hns_roce_dev {int /*<<< orphan*/  dev; } ;
struct hns_roce_cmd_mailbox {int /*<<< orphan*/  dma; struct hns_roce_v2_cq_context* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS_ROCE_CMD_QUERY_CQC ; 
 int /*<<< orphan*/  HNS_ROCE_CMD_TIMEOUT_MSECS ; 
 scalar_t__ IS_ERR (struct hns_roce_cmd_mailbox*) ; 
 int PTR_ERR (struct hns_roce_cmd_mailbox*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct hns_roce_cmd_mailbox* hns_roce_alloc_cmd_mailbox (struct hns_roce_dev*) ; 
 int hns_roce_cmd_mbox (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_free_cmd_mailbox (struct hns_roce_dev*,struct hns_roce_cmd_mailbox*) ; 
 int /*<<< orphan*/  memcpy (int*,struct hns_roce_v2_cq_context*,int) ; 

int hns_roce_v2_query_cqc_info(struct hns_roce_dev *hr_dev, u32 cqn,
			       int *buffer)
{
	struct hns_roce_v2_cq_context *cq_context;
	struct hns_roce_cmd_mailbox *mailbox;
	int ret;

	mailbox = hns_roce_alloc_cmd_mailbox(hr_dev);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);

	cq_context = mailbox->buf;
	ret = hns_roce_cmd_mbox(hr_dev, 0, mailbox->dma, cqn, 0,
				HNS_ROCE_CMD_QUERY_CQC,
				HNS_ROCE_CMD_TIMEOUT_MSECS);
	if (ret) {
		dev_err(hr_dev->dev, "QUERY cqc cmd process error\n");
		goto err_mailbox;
	}

	memcpy(buffer, cq_context, sizeof(*cq_context));

err_mailbox:
	hns_roce_free_cmd_mailbox(hr_dev, mailbox);

	return ret;
}