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
struct bc_state {int /*<<< orphan*/ ** commands; int /*<<< orphan*/ * rx_skb; int /*<<< orphan*/  channel; int /*<<< orphan*/  at_state; TYPE_1__* cs; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* freebcshw ) (struct bc_state*) ;} ;
struct TYPE_3__ {TYPE_2__* ops; } ;

/* Variables and functions */
 int AT_NUM ; 
 int /*<<< orphan*/  DEBUG_INIT ; 
 int /*<<< orphan*/  clear_at_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct bc_state*) ; 

__attribute__((used)) static void gigaset_freebcs(struct bc_state *bcs)
{
	int i;

	gig_dbg(DEBUG_INIT, "freeing bcs[%d]->hw", bcs->channel);
	bcs->cs->ops->freebcshw(bcs);

	gig_dbg(DEBUG_INIT, "clearing bcs[%d]->at_state", bcs->channel);
	clear_at_state(&bcs->at_state);
	gig_dbg(DEBUG_INIT, "freeing bcs[%d]->skb", bcs->channel);
	dev_kfree_skb(bcs->rx_skb);
	bcs->rx_skb = NULL;

	for (i = 0; i < AT_NUM; ++i) {
		kfree(bcs->commands[i]);
		bcs->commands[i] = NULL;
	}
}