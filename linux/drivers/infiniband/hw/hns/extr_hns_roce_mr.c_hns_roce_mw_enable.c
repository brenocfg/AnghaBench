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
struct hns_roce_mw {int enabled; int /*<<< orphan*/  rkey; } ;
struct hns_roce_mr_table {int /*<<< orphan*/  mtpt_table; } ;
struct TYPE_4__ {int num_mtpts; } ;
struct hns_roce_dev {TYPE_2__ caps; TYPE_1__* hw; struct device* dev; struct hns_roce_mr_table mr_table; } ;
struct hns_roce_cmd_mailbox {int /*<<< orphan*/  buf; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int (* mw_write_mtpt ) (int /*<<< orphan*/ ,struct hns_roce_mw*) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct hns_roce_cmd_mailbox*) ; 
 int PTR_ERR (struct hns_roce_cmd_mailbox*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct hns_roce_cmd_mailbox* hns_roce_alloc_cmd_mailbox (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  hns_roce_free_cmd_mailbox (struct hns_roce_dev*,struct hns_roce_cmd_mailbox*) ; 
 int hns_roce_sw2hw_mpt (struct hns_roce_dev*,struct hns_roce_cmd_mailbox*,unsigned long) ; 
 int hns_roce_table_get (struct hns_roce_dev*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  hns_roce_table_put (struct hns_roce_dev*,int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long key_to_hw_index (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,struct hns_roce_mw*) ; 

__attribute__((used)) static int hns_roce_mw_enable(struct hns_roce_dev *hr_dev,
			      struct hns_roce_mw *mw)
{
	struct hns_roce_mr_table *mr_table = &hr_dev->mr_table;
	struct hns_roce_cmd_mailbox *mailbox;
	struct device *dev = hr_dev->dev;
	unsigned long mtpt_idx = key_to_hw_index(mw->rkey);
	int ret;

	/* prepare HEM entry memory */
	ret = hns_roce_table_get(hr_dev, &mr_table->mtpt_table, mtpt_idx);
	if (ret)
		return ret;

	mailbox = hns_roce_alloc_cmd_mailbox(hr_dev);
	if (IS_ERR(mailbox)) {
		ret = PTR_ERR(mailbox);
		goto err_table;
	}

	ret = hr_dev->hw->mw_write_mtpt(mailbox->buf, mw);
	if (ret) {
		dev_err(dev, "MW write mtpt fail!\n");
		goto err_page;
	}

	ret = hns_roce_sw2hw_mpt(hr_dev, mailbox,
				 mtpt_idx & (hr_dev->caps.num_mtpts - 1));
	if (ret) {
		dev_err(dev, "MW sw2hw_mpt failed (%d)\n", ret);
		goto err_page;
	}

	mw->enabled = 1;

	hns_roce_free_cmd_mailbox(hr_dev, mailbox);

	return 0;

err_page:
	hns_roce_free_cmd_mailbox(hr_dev, mailbox);

err_table:
	hns_roce_table_put(hr_dev, &mr_table->mtpt_table, mtpt_idx);

	return ret;
}