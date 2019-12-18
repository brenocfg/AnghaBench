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
typedef  scalar_t__ u64 ;
struct mthca_mailbox {int /*<<< orphan*/  dma; int /*<<< orphan*/ * buf; } ;
struct mthca_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_MAP_ICM ; 
 int /*<<< orphan*/  CMD_TIME_CLASS_B ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mthca_mailbox*) ; 
 int PTR_ERR (struct mthca_mailbox*) ; 
 int /*<<< orphan*/  cpu_to_be64 (scalar_t__) ; 
 struct mthca_mailbox* mthca_alloc_mailbox (struct mthca_dev*,int /*<<< orphan*/ ) ; 
 int mthca_cmd (struct mthca_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_dbg (struct mthca_dev*,char*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  mthca_free_mailbox (struct mthca_dev*,struct mthca_mailbox*) ; 

int mthca_MAP_ICM_page(struct mthca_dev *dev, u64 dma_addr, u64 virt)
{
	struct mthca_mailbox *mailbox;
	__be64 *inbox;
	int err;

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);
	inbox = mailbox->buf;

	inbox[0] = cpu_to_be64(virt);
	inbox[1] = cpu_to_be64(dma_addr);

	err = mthca_cmd(dev, mailbox->dma, 1, 0, CMD_MAP_ICM,
			CMD_TIME_CLASS_B);

	mthca_free_mailbox(dev, mailbox);

	if (!err)
		mthca_dbg(dev, "Mapped page at %llx to %llx for ICM.\n",
			  (unsigned long long) dma_addr, (unsigned long long) virt);

	return err;
}