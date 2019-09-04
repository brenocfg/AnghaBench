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
typedef  int u32 ;
struct mthca_set_ib_param {int cap_mask; int si_guid; scalar_t__ reset_qkey_viol; scalar_t__ set_si_guid; } ;
struct mthca_mailbox {int* buf; int /*<<< orphan*/  dma; } ;
struct mthca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SET_IB ; 
 int /*<<< orphan*/  CMD_TIME_CLASS_B ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mthca_mailbox*) ; 
 int /*<<< orphan*/  MTHCA_PUT (int*,int,int) ; 
 int PTR_ERR (struct mthca_mailbox*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 struct mthca_mailbox* mthca_alloc_mailbox (struct mthca_dev*,int /*<<< orphan*/ ) ; 
 int mthca_cmd (struct mthca_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_free_mailbox (struct mthca_dev*,struct mthca_mailbox*) ; 

int mthca_SET_IB(struct mthca_dev *dev, struct mthca_set_ib_param *param,
		 int port)
{
	struct mthca_mailbox *mailbox;
	u32 *inbox;
	int err;
	u32 flags = 0;

#define SET_IB_IN_SIZE         0x40
#define SET_IB_FLAGS_OFFSET    0x00
#define SET_IB_FLAG_SIG        (1 << 18)
#define SET_IB_FLAG_RQK        (1 <<  0)
#define SET_IB_CAP_MASK_OFFSET 0x04
#define SET_IB_SI_GUID_OFFSET  0x08

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);
	inbox = mailbox->buf;

	memset(inbox, 0, SET_IB_IN_SIZE);

	flags |= param->set_si_guid     ? SET_IB_FLAG_SIG : 0;
	flags |= param->reset_qkey_viol ? SET_IB_FLAG_RQK : 0;
	MTHCA_PUT(inbox, flags, SET_IB_FLAGS_OFFSET);

	MTHCA_PUT(inbox, param->cap_mask, SET_IB_CAP_MASK_OFFSET);
	MTHCA_PUT(inbox, param->si_guid,  SET_IB_SI_GUID_OFFSET);

	err = mthca_cmd(dev, mailbox->dma, port, 0, CMD_SET_IB,
			CMD_TIME_CLASS_B);

	mthca_free_mailbox(dev, mailbox);
	return err;
}