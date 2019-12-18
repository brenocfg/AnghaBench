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
struct ppp_net {int /*<<< orphan*/  all_channels_lock; } ;
struct ppp_channel {struct channel* ppp; } ;
struct TYPE_2__ {int dead; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  rwait; } ;
struct channel {TYPE_1__ file; int /*<<< orphan*/  list; int /*<<< orphan*/  chan_net; int /*<<< orphan*/  chan_sem; int /*<<< orphan*/  downl; int /*<<< orphan*/ * chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppp_destroy_channel (struct channel*) ; 
 int /*<<< orphan*/  ppp_disconnect_channel (struct channel*) ; 
 struct ppp_net* ppp_pernet (int /*<<< orphan*/ ) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void
ppp_unregister_channel(struct ppp_channel *chan)
{
	struct channel *pch = chan->ppp;
	struct ppp_net *pn;

	if (!pch)
		return;		/* should never happen */

	chan->ppp = NULL;

	/*
	 * This ensures that we have returned from any calls into the
	 * the channel's start_xmit or ioctl routine before we proceed.
	 */
	down_write(&pch->chan_sem);
	spin_lock_bh(&pch->downl);
	pch->chan = NULL;
	spin_unlock_bh(&pch->downl);
	up_write(&pch->chan_sem);
	ppp_disconnect_channel(pch);

	pn = ppp_pernet(pch->chan_net);
	spin_lock_bh(&pn->all_channels_lock);
	list_del(&pch->list);
	spin_unlock_bh(&pn->all_channels_lock);

	pch->file.dead = 1;
	wake_up_interruptible(&pch->file.rwait);
	if (refcount_dec_and_test(&pch->file.refcnt))
		ppp_destroy_channel(pch);
}