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
struct TYPE_2__ {int /*<<< orphan*/  pool; } ;
struct hns_roce_dev {TYPE_1__ cmd; } ;
struct hns_roce_cmd_mailbox {int /*<<< orphan*/  buf; int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct hns_roce_cmd_mailbox* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hns_roce_cmd_mailbox*) ; 
 struct hns_roce_cmd_mailbox* kmalloc (int,int /*<<< orphan*/ ) ; 

struct hns_roce_cmd_mailbox
	*hns_roce_alloc_cmd_mailbox(struct hns_roce_dev *hr_dev)
{
	struct hns_roce_cmd_mailbox *mailbox;

	mailbox = kmalloc(sizeof(*mailbox), GFP_KERNEL);
	if (!mailbox)
		return ERR_PTR(-ENOMEM);

	mailbox->buf = dma_pool_alloc(hr_dev->cmd.pool, GFP_KERNEL,
				      &mailbox->dma);
	if (!mailbox->buf) {
		kfree(mailbox);
		return ERR_PTR(-ENOMEM);
	}

	return mailbox;
}