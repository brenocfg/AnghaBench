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
struct sti_mbox_device {int* enabled; } ;
struct sti_channel {unsigned int instance; unsigned int channel; struct sti_mbox_device* mdev; } ;
struct mbox_chan {struct sti_channel* con_priv; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 

__attribute__((used)) static inline bool sti_mbox_channel_is_enabled(struct mbox_chan *chan)
{
	struct sti_channel *chan_info = chan->con_priv;
	struct sti_mbox_device *mdev = chan_info->mdev;
	unsigned int instance = chan_info->instance;
	unsigned int channel = chan_info->channel;

	return mdev->enabled[instance] & BIT(channel);
}