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
struct TYPE_3__ {int (* peek_data ) (struct mbox_chan*) ;} ;

/* Variables and functions */
 int stub1 (struct mbox_chan*) ; 

bool mbox_client_peek_data(struct mbox_chan *chan)
{
	if (chan->mbox->ops->peek_data)
		return chan->mbox->ops->peek_data(chan);

	return false;
}