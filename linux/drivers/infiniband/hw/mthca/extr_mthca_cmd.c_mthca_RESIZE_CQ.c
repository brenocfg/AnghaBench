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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mthca_mailbox {int /*<<< orphan*/  dma; int /*<<< orphan*/ * buf; } ;
struct mthca_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RESIZE_CQ ; 
 int /*<<< orphan*/  CMD_TIME_CLASS_B ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mthca_mailbox*) ; 
 int /*<<< orphan*/  MTHCA_PUT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct mthca_mailbox*) ; 
 int /*<<< orphan*/  RESIZE_CQ_IN_SIZE ; 
 int /*<<< orphan*/  RESIZE_CQ_LKEY_OFFSET ; 
 int /*<<< orphan*/  RESIZE_CQ_LOG_SIZE_OFFSET ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mthca_mailbox* mthca_alloc_mailbox (struct mthca_dev*,int /*<<< orphan*/ ) ; 
 int mthca_cmd (struct mthca_dev*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_free_mailbox (struct mthca_dev*,struct mthca_mailbox*) ; 

int mthca_RESIZE_CQ(struct mthca_dev *dev, int cq_num, u32 lkey, u8 log_size)
{
	struct mthca_mailbox *mailbox;
	__be32 *inbox;
	int err;

#define RESIZE_CQ_IN_SIZE		0x40
#define RESIZE_CQ_LOG_SIZE_OFFSET	0x0c
#define RESIZE_CQ_LKEY_OFFSET		0x1c

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);
	inbox = mailbox->buf;

	memset(inbox, 0, RESIZE_CQ_IN_SIZE);
	/*
	 * Leave start address fields zeroed out -- mthca assumes that
	 * MRs for CQs always start at virtual address 0.
	 */
	MTHCA_PUT(inbox, log_size, RESIZE_CQ_LOG_SIZE_OFFSET);
	MTHCA_PUT(inbox, lkey,     RESIZE_CQ_LKEY_OFFSET);

	err = mthca_cmd(dev, mailbox->dma, cq_num, 1, CMD_RESIZE_CQ,
			CMD_TIME_CLASS_B);

	mthca_free_mailbox(dev, mailbox);
	return err;
}