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
struct mbox_controller {int num_chans; int txdone_irq; int txdone_poll; int txpoll_period; TYPE_2__* chans; int /*<<< orphan*/ * ops; struct device* dev; } ;
struct pdc_state {struct mbox_controller mbc; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct pdc_state* con_priv; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_crit (struct device*,char*,int) ; 
 TYPE_2__* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 int devm_mbox_controller_register (struct device*,struct mbox_controller*) ; 
 int /*<<< orphan*/  pdc_mbox_chan_ops ; 

__attribute__((used)) static int pdc_mb_init(struct pdc_state *pdcs)
{
	struct device *dev = &pdcs->pdev->dev;
	struct mbox_controller *mbc;
	int chan_index;
	int err;

	mbc = &pdcs->mbc;
	mbc->dev = dev;
	mbc->ops = &pdc_mbox_chan_ops;
	mbc->num_chans = 1;
	mbc->chans = devm_kcalloc(dev, mbc->num_chans, sizeof(*mbc->chans),
				  GFP_KERNEL);
	if (!mbc->chans)
		return -ENOMEM;

	mbc->txdone_irq = false;
	mbc->txdone_poll = true;
	mbc->txpoll_period = 1;
	for (chan_index = 0; chan_index < mbc->num_chans; chan_index++)
		mbc->chans[chan_index].con_priv = pdcs;

	/* Register mailbox controller */
	err = devm_mbox_controller_register(dev, mbc);
	if (err) {
		dev_crit(dev,
			 "Failed to register PDC mailbox controller. Error %d.",
			 err);
		return err;
	}
	return 0;
}