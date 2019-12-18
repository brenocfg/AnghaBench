#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_4__ {scalar_t__ qlen; int /*<<< orphan*/  lock; } ;
struct fcoe_port {int fcoe_pending_queue_active; scalar_t__ min_queue_depth; scalar_t__ max_queue_depth; TYPE_1__ fcoe_pending_queue; int /*<<< orphan*/  timer; } ;
struct fc_lport {int qfull; } ;

/* Variables and functions */
 struct sk_buff* __skb_dequeue (TYPE_1__*) ; 
 int /*<<< orphan*/  __skb_queue_head (TYPE_1__*,struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_queue_tail (TYPE_1__*,struct sk_buff*) ; 
 int fcoe_start_io (struct sk_buff*) ; 
 scalar_t__ jiffies ; 
 struct fcoe_port* lport_priv (struct fc_lport*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

void fcoe_check_wait_queue(struct fc_lport *lport, struct sk_buff *skb)
{
	struct fcoe_port *port = lport_priv(lport);
	int rc;

	spin_lock_bh(&port->fcoe_pending_queue.lock);

	if (skb)
		__skb_queue_tail(&port->fcoe_pending_queue, skb);

	if (port->fcoe_pending_queue_active)
		goto out;
	port->fcoe_pending_queue_active = 1;

	while (port->fcoe_pending_queue.qlen) {
		/* keep qlen > 0 until fcoe_start_io succeeds */
		port->fcoe_pending_queue.qlen++;
		skb = __skb_dequeue(&port->fcoe_pending_queue);

		spin_unlock_bh(&port->fcoe_pending_queue.lock);
		rc = fcoe_start_io(skb);
		spin_lock_bh(&port->fcoe_pending_queue.lock);

		if (rc) {
			__skb_queue_head(&port->fcoe_pending_queue, skb);
			/* undo temporary increment above */
			port->fcoe_pending_queue.qlen--;
			break;
		}
		/* undo temporary increment above */
		port->fcoe_pending_queue.qlen--;
	}

	if (port->fcoe_pending_queue.qlen < port->min_queue_depth)
		lport->qfull = 0;
	if (port->fcoe_pending_queue.qlen && !timer_pending(&port->timer))
		mod_timer(&port->timer, jiffies + 2);
	port->fcoe_pending_queue_active = 0;
out:
	if (port->fcoe_pending_queue.qlen > port->max_queue_depth)
		lport->qfull = 1;
	spin_unlock_bh(&port->fcoe_pending_queue.lock);
}