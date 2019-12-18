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
struct TYPE_2__ {int /*<<< orphan*/  rq; int /*<<< orphan*/  xq; int /*<<< orphan*/  dead; } ;
struct channel {TYPE_1__ file; int /*<<< orphan*/ * chan_net; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  channel_count ; 
 int /*<<< orphan*/  kfree (struct channel*) ; 
 int /*<<< orphan*/  pr_err (char*,struct channel*) ; 
 int /*<<< orphan*/  put_net (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ppp_destroy_channel(struct channel *pch)
{
	put_net(pch->chan_net);
	pch->chan_net = NULL;

	atomic_dec(&channel_count);

	if (!pch->file.dead) {
		/* "can't happen" */
		pr_err("ppp: destroying undead channel %p !\n", pch);
		return;
	}
	skb_queue_purge(&pch->file.xq);
	skb_queue_purge(&pch->file.rq);
	kfree(pch);
}