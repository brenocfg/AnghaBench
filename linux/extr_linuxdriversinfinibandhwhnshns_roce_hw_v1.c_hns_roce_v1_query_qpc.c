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
struct hns_roce_qp_context {int dummy; } ;
struct hns_roce_qp {int /*<<< orphan*/  qpn; } ;
struct hns_roce_dev {TYPE_1__* pdev; } ;
struct hns_roce_cmd_mailbox {int /*<<< orphan*/  buf; int /*<<< orphan*/  dma; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS_ROCE_CMD_QUERY_QP ; 
 int /*<<< orphan*/  HNS_ROCE_CMD_TIMEOUT_MSECS ; 
 scalar_t__ IS_ERR (struct hns_roce_cmd_mailbox*) ; 
 int PTR_ERR (struct hns_roce_cmd_mailbox*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct hns_roce_cmd_mailbox* hns_roce_alloc_cmd_mailbox (struct hns_roce_dev*) ; 
 int hns_roce_cmd_mbox (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_free_cmd_mailbox (struct hns_roce_dev*,struct hns_roce_cmd_mailbox*) ; 
 int /*<<< orphan*/  memcpy (struct hns_roce_qp_context*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hns_roce_v1_query_qpc(struct hns_roce_dev *hr_dev,
				 struct hns_roce_qp *hr_qp,
				 struct hns_roce_qp_context *hr_context)
{
	struct hns_roce_cmd_mailbox *mailbox;
	int ret;

	mailbox = hns_roce_alloc_cmd_mailbox(hr_dev);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);

	ret = hns_roce_cmd_mbox(hr_dev, 0, mailbox->dma, hr_qp->qpn, 0,
				HNS_ROCE_CMD_QUERY_QP,
				HNS_ROCE_CMD_TIMEOUT_MSECS);
	if (!ret)
		memcpy(hr_context, mailbox->buf, sizeof(*hr_context));
	else
		dev_err(&hr_dev->pdev->dev, "QUERY QP cmd process error\n");

	hns_roce_free_cmd_mailbox(hr_dev, mailbox);

	return ret;
}