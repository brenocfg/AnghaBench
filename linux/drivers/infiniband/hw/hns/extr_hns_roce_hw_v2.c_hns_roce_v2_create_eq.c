#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct hns_roce_eq {TYPE_2__* buf_list; int /*<<< orphan*/  eqn; } ;
struct TYPE_4__ {int eqe_buf_pg_sz; int /*<<< orphan*/  eqe_hop_num; } ;
struct hns_roce_dev {TYPE_1__ caps; struct device* dev; } ;
struct hns_roce_cmd_mailbox {int /*<<< orphan*/  dma; int /*<<< orphan*/  buf; } ;
struct hns_roce_buf_list {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  map; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HNS_ROCE_CMD_TIMEOUT_MSECS ; 
 scalar_t__ IS_ERR (struct hns_roce_cmd_mailbox*) ; 
 int PAGE_SHIFT ; 
 int PTR_ERR (struct hns_roce_cmd_mailbox*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hns_roce_cmd_mailbox* hns_roce_alloc_cmd_mailbox (struct hns_roce_dev*) ; 
 int hns_roce_cmd_mbox (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_config_eqc (struct hns_roce_dev*,struct hns_roce_eq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_free_cmd_mailbox (struct hns_roce_dev*,struct hns_roce_cmd_mailbox*) ; 
 int hns_roce_mhop_alloc_eq (struct hns_roce_dev*,struct hns_roce_eq*) ; 
 int /*<<< orphan*/  hns_roce_mhop_free_eq (struct hns_roce_dev*,struct hns_roce_eq*) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_roce_v2_create_eq(struct hns_roce_dev *hr_dev,
				 struct hns_roce_eq *eq,
				 unsigned int eq_cmd)
{
	struct device *dev = hr_dev->dev;
	struct hns_roce_cmd_mailbox *mailbox;
	u32 buf_chk_sz = 0;
	int ret;

	/* Allocate mailbox memory */
	mailbox = hns_roce_alloc_cmd_mailbox(hr_dev);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);

	if (!hr_dev->caps.eqe_hop_num) {
		buf_chk_sz = 1 << (hr_dev->caps.eqe_buf_pg_sz + PAGE_SHIFT);

		eq->buf_list = kzalloc(sizeof(struct hns_roce_buf_list),
				       GFP_KERNEL);
		if (!eq->buf_list) {
			ret = -ENOMEM;
			goto free_cmd_mbox;
		}

		eq->buf_list->buf = dma_alloc_coherent(dev, buf_chk_sz,
						       &(eq->buf_list->map),
						       GFP_KERNEL);
		if (!eq->buf_list->buf) {
			ret = -ENOMEM;
			goto err_alloc_buf;
		}

	} else {
		ret = hns_roce_mhop_alloc_eq(hr_dev, eq);
		if (ret) {
			ret = -ENOMEM;
			goto free_cmd_mbox;
		}
	}

	hns_roce_config_eqc(hr_dev, eq, mailbox->buf);

	ret = hns_roce_cmd_mbox(hr_dev, mailbox->dma, 0, eq->eqn, 0,
				eq_cmd, HNS_ROCE_CMD_TIMEOUT_MSECS);
	if (ret) {
		dev_err(dev, "[mailbox cmd] create eqc failed.\n");
		goto err_cmd_mbox;
	}

	hns_roce_free_cmd_mailbox(hr_dev, mailbox);

	return 0;

err_cmd_mbox:
	if (!hr_dev->caps.eqe_hop_num)
		dma_free_coherent(dev, buf_chk_sz, eq->buf_list->buf,
				  eq->buf_list->map);
	else {
		hns_roce_mhop_free_eq(hr_dev, eq);
		goto free_cmd_mbox;
	}

err_alloc_buf:
	kfree(eq->buf_list);

free_cmd_mbox:
	hns_roce_free_cmd_mailbox(hr_dev, mailbox);

	return ret;
}