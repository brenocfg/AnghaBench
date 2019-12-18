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
struct sti_channel {unsigned int instance; unsigned int channel; } ;
struct mbox_controller {int num_chans; int /*<<< orphan*/  dev; struct mbox_chan* chans; } ;
struct mbox_chan {struct sti_channel* con_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static inline
struct mbox_chan *sti_mbox_to_channel(struct mbox_controller *mbox,
				      unsigned int instance,
				      unsigned int channel)
{
	struct sti_channel *chan_info;
	int i;

	for (i = 0; i < mbox->num_chans; i++) {
		chan_info = mbox->chans[i].con_priv;
		if (chan_info &&
		    chan_info->instance == instance &&
		    chan_info->channel == channel)
			return &mbox->chans[i];
	}

	dev_err(mbox->dev,
		"Channel not registered: instance: %d channel: %d\n",
		instance, channel);

	return NULL;
}