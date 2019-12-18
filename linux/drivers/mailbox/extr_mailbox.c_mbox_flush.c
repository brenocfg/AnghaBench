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
struct mbox_chan {TYPE_2__* mbox; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* flush ) (struct mbox_chan*,unsigned long) ;} ;

/* Variables and functions */
 int ENOTSUPP ; 
 int stub1 (struct mbox_chan*,unsigned long) ; 
 int /*<<< orphan*/  tx_tick (struct mbox_chan*,int) ; 

int mbox_flush(struct mbox_chan *chan, unsigned long timeout)
{
	int ret;

	if (!chan->mbox->ops->flush)
		return -ENOTSUPP;

	ret = chan->mbox->ops->flush(chan, timeout);
	if (ret < 0)
		tx_tick(chan, ret);

	return ret;
}