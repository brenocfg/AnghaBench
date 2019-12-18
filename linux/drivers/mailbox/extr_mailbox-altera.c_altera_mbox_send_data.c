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
struct mbox_chan {int dummy; } ;
struct altera_mbox {scalar_t__ mbox_base; scalar_t__ intr_mode; int /*<<< orphan*/  dev; int /*<<< orphan*/  is_sender; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ MAILBOX_CMD_REG ; 
 scalar_t__ MAILBOX_PTR_REG ; 
 size_t MBOX_CMD ; 
 size_t MBOX_PTR ; 
 scalar_t__ altera_mbox_full (struct altera_mbox*) ; 
 int /*<<< orphan*/  altera_mbox_tx_intmask (struct altera_mbox*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct altera_mbox* mbox_chan_to_altera_mbox (struct mbox_chan*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int altera_mbox_send_data(struct mbox_chan *chan, void *data)
{
	struct altera_mbox *mbox = mbox_chan_to_altera_mbox(chan);
	u32 *udata = (u32 *)data;

	if (!mbox || !data)
		return -EINVAL;
	if (!mbox->is_sender) {
		dev_warn(mbox->dev,
			 "failed to send. This is receiver mailbox.\n");
		return -EINVAL;
	}

	if (altera_mbox_full(mbox))
		return -EBUSY;

	/* Enable interrupt before send */
	if (mbox->intr_mode)
		altera_mbox_tx_intmask(mbox, true);

	/* Pointer register must write before command register */
	writel_relaxed(udata[MBOX_PTR], mbox->mbox_base + MAILBOX_PTR_REG);
	writel_relaxed(udata[MBOX_CMD], mbox->mbox_base + MAILBOX_CMD_REG);

	return 0;
}