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
struct hns_roce_cmd_mailbox {int /*<<< orphan*/  dma; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hns_roce_cmd_mailbox*) ; 

void hns_roce_free_cmd_mailbox(struct hns_roce_dev *hr_dev,
			       struct hns_roce_cmd_mailbox *mailbox)
{
	if (!mailbox)
		return;

	dma_pool_free(hr_dev->cmd.pool, mailbox->buf, mailbox->dma);
	kfree(mailbox);
}