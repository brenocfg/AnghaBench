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
struct mad_rmpp_recv {int /*<<< orphan*/  newwin; int /*<<< orphan*/  timeout_work; int /*<<< orphan*/  state; int /*<<< orphan*/  refcount; } ;
struct ib_mad_recv_wc {int /*<<< orphan*/  recv_buf; } ;
struct ib_mad_agent_private {TYPE_2__* qp_info; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {TYPE_1__* port_priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  RMPP_STATE_COMPLETE ; 
 int /*<<< orphan*/  ack_recv (struct mad_rmpp_recv*,struct ib_mad_recv_wc*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete_rmpp (struct mad_rmpp_recv*) ; 
 struct ib_mad_recv_wc* continue_rmpp (struct ib_mad_agent_private*,struct ib_mad_recv_wc*) ; 
 struct mad_rmpp_recv* create_rmpp_recv (struct ib_mad_agent_private*,struct ib_mad_recv_wc*) ; 
 int /*<<< orphan*/  deref_rmpp_recv (struct mad_rmpp_recv*) ; 
 int /*<<< orphan*/  destroy_rmpp_recv (struct mad_rmpp_recv*) ; 
 scalar_t__ get_last_flag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_free_recv_mad (struct ib_mad_recv_wc*) ; 
 scalar_t__ insert_rmpp_recv (struct ib_mad_agent_private*,struct mad_rmpp_recv*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ window_size (struct ib_mad_agent_private*) ; 

__attribute__((used)) static struct ib_mad_recv_wc *
start_rmpp(struct ib_mad_agent_private *agent,
	   struct ib_mad_recv_wc *mad_recv_wc)
{
	struct mad_rmpp_recv *rmpp_recv;
	unsigned long flags;

	rmpp_recv = create_rmpp_recv(agent, mad_recv_wc);
	if (!rmpp_recv) {
		ib_free_recv_mad(mad_recv_wc);
		return NULL;
	}

	spin_lock_irqsave(&agent->lock, flags);
	if (insert_rmpp_recv(agent, rmpp_recv)) {
		spin_unlock_irqrestore(&agent->lock, flags);
		/* duplicate first MAD */
		destroy_rmpp_recv(rmpp_recv);
		return continue_rmpp(agent, mad_recv_wc);
	}
	atomic_inc(&rmpp_recv->refcount);

	if (get_last_flag(&mad_recv_wc->recv_buf)) {
		rmpp_recv->state = RMPP_STATE_COMPLETE;
		spin_unlock_irqrestore(&agent->lock, flags);
		complete_rmpp(rmpp_recv);
	} else {
		spin_unlock_irqrestore(&agent->lock, flags);
		/* 40 seconds until we can find the packet lifetimes */
		queue_delayed_work(agent->qp_info->port_priv->wq,
				   &rmpp_recv->timeout_work,
				   msecs_to_jiffies(40000));
		rmpp_recv->newwin += window_size(agent);
		ack_recv(rmpp_recv, mad_recv_wc);
		mad_recv_wc = NULL;
	}
	deref_rmpp_recv(rmpp_recv);
	return mad_recv_wc;
}