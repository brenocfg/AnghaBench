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
struct sti_channel {TYPE_1__* mdev; } ;
struct mbox_controller {int num_chans; int /*<<< orphan*/  dev; struct mbox_chan* chans; } ;
struct mbox_chan {struct sti_channel* con_priv; } ;
struct TYPE_2__ {struct mbox_controller* mbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sti_mbox_clear_irq (struct mbox_chan*) ; 
 int /*<<< orphan*/  sti_mbox_disable_channel (struct mbox_chan*) ; 

__attribute__((used)) static void sti_mbox_shutdown_chan(struct mbox_chan *chan)
{
	struct sti_channel *chan_info = chan->con_priv;
	struct mbox_controller *mbox = chan_info->mdev->mbox;
	int i;

	for (i = 0; i < mbox->num_chans; i++)
		if (chan == &mbox->chans[i])
			break;

	if (mbox->num_chans == i) {
		dev_warn(mbox->dev, "Request to free non-existent channel\n");
		return;
	}

	/* Reset channel */
	sti_mbox_disable_channel(chan);
	sti_mbox_clear_irq(chan);
	chan->con_priv = NULL;
}