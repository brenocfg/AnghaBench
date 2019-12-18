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
struct mbox_chan {TYPE_1__* cl; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rx_callback ) (TYPE_1__*,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,void*) ; 

void mbox_chan_received_data(struct mbox_chan *chan, void *mssg)
{
	/* No buffering the received data */
	if (chan->cl->rx_callback)
		chan->cl->rx_callback(chan->cl, mssg);
}