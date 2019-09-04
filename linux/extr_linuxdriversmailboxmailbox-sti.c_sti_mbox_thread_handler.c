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
struct sti_mbox_pdata {unsigned int num_inst; } ;
struct sti_mbox_device {int /*<<< orphan*/  dev; } ;
struct mbox_chan {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct sti_mbox_pdata* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_chan_received_data (struct mbox_chan*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sti_mbox_clear_irq (struct mbox_chan*) ; 
 int /*<<< orphan*/  sti_mbox_enable_channel (struct mbox_chan*) ; 
 struct mbox_chan* sti_mbox_irq_to_channel (struct sti_mbox_device*,unsigned int) ; 

__attribute__((used)) static irqreturn_t sti_mbox_thread_handler(int irq, void *data)
{
	struct sti_mbox_device *mdev = data;
	struct sti_mbox_pdata *pdata = dev_get_platdata(mdev->dev);
	struct mbox_chan *chan;
	unsigned int instance;

	for (instance = 0; instance < pdata->num_inst; instance++) {
keep_looking:
		chan = sti_mbox_irq_to_channel(mdev, instance);
		if (!chan)
			continue;

		mbox_chan_received_data(chan, NULL);
		sti_mbox_clear_irq(chan);
		sti_mbox_enable_channel(chan);
		goto keep_looking;
	}

	return IRQ_HANDLED;
}