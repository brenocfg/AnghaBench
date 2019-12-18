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
struct TYPE_4__ {int /*<<< orphan*/  function; } ;
struct mbox_controller {int num_chans; int /*<<< orphan*/  node; scalar_t__ of_xlate; struct mbox_chan* chans; TYPE_2__ poll_hrt; int /*<<< orphan*/  dev; TYPE_1__* ops; scalar_t__ txdone_poll; scalar_t__ txdone_irq; } ;
struct mbox_chan {int txdone_method; int /*<<< orphan*/  lock; struct mbox_controller* mbox; int /*<<< orphan*/ * cl; } ;
struct TYPE_3__ {int /*<<< orphan*/  last_tx_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int EINVAL ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int TXDONE_BY_ACK ; 
 int TXDONE_BY_IRQ ; 
 int TXDONE_BY_POLL ; 
 int /*<<< orphan*/  con_mutex ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbox_cons ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ of_mbox_index_xlate ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txdone_hrtimer ; 

int mbox_controller_register(struct mbox_controller *mbox)
{
	int i, txdone;

	/* Sanity check */
	if (!mbox || !mbox->dev || !mbox->ops || !mbox->num_chans)
		return -EINVAL;

	if (mbox->txdone_irq)
		txdone = TXDONE_BY_IRQ;
	else if (mbox->txdone_poll)
		txdone = TXDONE_BY_POLL;
	else /* It has to be ACK then */
		txdone = TXDONE_BY_ACK;

	if (txdone == TXDONE_BY_POLL) {

		if (!mbox->ops->last_tx_done) {
			dev_err(mbox->dev, "last_tx_done method is absent\n");
			return -EINVAL;
		}

		hrtimer_init(&mbox->poll_hrt, CLOCK_MONOTONIC,
			     HRTIMER_MODE_REL);
		mbox->poll_hrt.function = txdone_hrtimer;
	}

	for (i = 0; i < mbox->num_chans; i++) {
		struct mbox_chan *chan = &mbox->chans[i];

		chan->cl = NULL;
		chan->mbox = mbox;
		chan->txdone_method = txdone;
		spin_lock_init(&chan->lock);
	}

	if (!mbox->of_xlate)
		mbox->of_xlate = of_mbox_index_xlate;

	mutex_lock(&con_mutex);
	list_add_tail(&mbox->node, &mbox_cons);
	mutex_unlock(&con_mutex);

	return 0;
}