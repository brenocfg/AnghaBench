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
struct omap_mbox {scalar_t__ send_no_irq; } ;
struct mbox_chan {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct omap_mbox* mbox_chan_to_omap_mbox (struct mbox_chan*) ; 
 int omap_mbox_chan_send (struct omap_mbox*,int /*<<< orphan*/ ) ; 
 int omap_mbox_chan_send_noirq (struct omap_mbox*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_mbox_message (void*) ; 

__attribute__((used)) static int omap_mbox_chan_send_data(struct mbox_chan *chan, void *data)
{
	struct omap_mbox *mbox = mbox_chan_to_omap_mbox(chan);
	int ret;
	u32 msg = omap_mbox_message(data);

	if (!mbox)
		return -EINVAL;

	if (mbox->send_no_irq)
		ret = omap_mbox_chan_send_noirq(mbox, msg);
	else
		ret = omap_mbox_chan_send(mbox, msg);

	return ret;
}