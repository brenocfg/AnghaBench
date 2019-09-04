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
struct mbox_chan {int dummy; } ;
struct altera_mbox {int dummy; } ;

/* Variables and functions */
 scalar_t__ altera_mbox_full (struct altera_mbox*) ; 
 struct altera_mbox* mbox_chan_to_altera_mbox (struct mbox_chan*) ; 

__attribute__((used)) static bool altera_mbox_last_tx_done(struct mbox_chan *chan)
{
	struct altera_mbox *mbox = mbox_chan_to_altera_mbox(chan);

	/* Return false if mailbox is full */
	return altera_mbox_full(mbox) ? false : true;
}