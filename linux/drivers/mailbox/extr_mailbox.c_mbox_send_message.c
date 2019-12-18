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
struct mbox_chan {int /*<<< orphan*/  tx_complete; TYPE_2__* cl; TYPE_1__* mbox; } ;
struct TYPE_4__ {int tx_tout; scalar_t__ tx_block; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIME ; 
 int add_to_rbuf (struct mbox_chan*,void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msg_submit (struct mbox_chan*) ; 
 int /*<<< orphan*/  tx_tick (struct mbox_chan*,int) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

int mbox_send_message(struct mbox_chan *chan, void *mssg)
{
	int t;

	if (!chan || !chan->cl)
		return -EINVAL;

	t = add_to_rbuf(chan, mssg);
	if (t < 0) {
		dev_err(chan->mbox->dev, "Try increasing MBOX_TX_QUEUE_LEN\n");
		return t;
	}

	msg_submit(chan);

	if (chan->cl->tx_block) {
		unsigned long wait;
		int ret;

		if (!chan->cl->tx_tout) /* wait forever */
			wait = msecs_to_jiffies(3600000);
		else
			wait = msecs_to_jiffies(chan->cl->tx_tout);

		ret = wait_for_completion_timeout(&chan->tx_complete, wait);
		if (ret == 0) {
			t = -ETIME;
			tx_tick(chan, t);
		}
	}

	return t;
}