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
struct tb_ctl {int running; int /*<<< orphan*/  request_queue; int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; int /*<<< orphan*/  request_queue_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tb_ctl_WARN (struct tb_ctl*,char*) ; 
 int /*<<< orphan*/  tb_ctl_dbg (struct tb_ctl*,char*) ; 
 int /*<<< orphan*/  tb_ring_stop (int /*<<< orphan*/ ) ; 

void tb_ctl_stop(struct tb_ctl *ctl)
{
	mutex_lock(&ctl->request_queue_lock);
	ctl->running = false;
	mutex_unlock(&ctl->request_queue_lock);

	tb_ring_stop(ctl->rx);
	tb_ring_stop(ctl->tx);

	if (!list_empty(&ctl->request_queue))
		tb_ctl_WARN(ctl, "dangling request in request_queue\n");
	INIT_LIST_HEAD(&ctl->request_queue);
	tb_ctl_dbg(ctl, "control channel stopped\n");
}