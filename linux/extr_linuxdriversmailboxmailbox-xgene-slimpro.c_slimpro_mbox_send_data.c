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
struct slimpro_mbox_chan {int dummy; } ;
struct mbox_chan {struct slimpro_mbox_chan* con_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mb_chan_send_msg (struct slimpro_mbox_chan*,void*) ; 

__attribute__((used)) static int slimpro_mbox_send_data(struct mbox_chan *chan, void *msg)
{
	struct slimpro_mbox_chan *mb_chan = chan->con_priv;

	mb_chan_send_msg(mb_chan, msg);
	return 0;
}