#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mad_rmpp_recv {scalar_t__ state; int newwin; int last_ack; int seg_num; int /*<<< orphan*/  lock; struct ib_mad_recv_buf* cur_seg_buf; TYPE_1__* rmpp_wc; } ;
struct TYPE_5__ {int /*<<< orphan*/  list; } ;
struct ib_mad_recv_wc {TYPE_2__ recv_buf; } ;
struct ib_mad_recv_buf {int /*<<< orphan*/  list; } ;
struct ib_mad_agent_private {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rmpp_list; } ;

/* Variables and functions */
 scalar_t__ RMPP_STATE_COMPLETE ; 
 scalar_t__ RMPP_STATE_TIMEOUT ; 
 int /*<<< orphan*/  ack_recv (struct mad_rmpp_recv*,struct ib_mad_recv_wc*) ; 
 struct mad_rmpp_recv* acquire_rmpp_recv (struct ib_mad_agent_private*,struct ib_mad_recv_wc*) ; 
 struct ib_mad_recv_wc* complete_rmpp (struct mad_rmpp_recv*) ; 
 int /*<<< orphan*/  deref_rmpp_recv (struct mad_rmpp_recv*) ; 
 struct ib_mad_recv_buf* find_seg_location (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_last_flag (struct ib_mad_recv_buf*) ; 
 int get_seg_num (TYPE_2__*) ; 
 int /*<<< orphan*/  ib_free_recv_mad (struct ib_mad_recv_wc*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  update_seg_num (struct mad_rmpp_recv*,TYPE_2__*) ; 
 scalar_t__ window_size (struct ib_mad_agent_private*) ; 

__attribute__((used)) static struct ib_mad_recv_wc *
continue_rmpp(struct ib_mad_agent_private *agent,
	      struct ib_mad_recv_wc *mad_recv_wc)
{
	struct mad_rmpp_recv *rmpp_recv;
	struct ib_mad_recv_buf *prev_buf;
	struct ib_mad_recv_wc *done_wc;
	int seg_num;
	unsigned long flags;

	rmpp_recv = acquire_rmpp_recv(agent, mad_recv_wc);
	if (!rmpp_recv)
		goto drop1;

	seg_num = get_seg_num(&mad_recv_wc->recv_buf);

	spin_lock_irqsave(&rmpp_recv->lock, flags);
	if ((rmpp_recv->state == RMPP_STATE_TIMEOUT) ||
	    (seg_num > rmpp_recv->newwin))
		goto drop3;

	if ((seg_num <= rmpp_recv->last_ack) ||
	    (rmpp_recv->state == RMPP_STATE_COMPLETE)) {
		spin_unlock_irqrestore(&rmpp_recv->lock, flags);
		ack_recv(rmpp_recv, mad_recv_wc);
		goto drop2;
	}

	prev_buf = find_seg_location(&rmpp_recv->rmpp_wc->rmpp_list, seg_num);
	if (!prev_buf)
		goto drop3;

	done_wc = NULL;
	list_add(&mad_recv_wc->recv_buf.list, &prev_buf->list);
	if (rmpp_recv->cur_seg_buf == prev_buf) {
		update_seg_num(rmpp_recv, &mad_recv_wc->recv_buf);
		if (get_last_flag(rmpp_recv->cur_seg_buf)) {
			rmpp_recv->state = RMPP_STATE_COMPLETE;
			spin_unlock_irqrestore(&rmpp_recv->lock, flags);
			done_wc = complete_rmpp(rmpp_recv);
			goto out;
		} else if (rmpp_recv->seg_num == rmpp_recv->newwin) {
			rmpp_recv->newwin += window_size(agent);
			spin_unlock_irqrestore(&rmpp_recv->lock, flags);
			ack_recv(rmpp_recv, mad_recv_wc);
			goto out;
		}
	}
	spin_unlock_irqrestore(&rmpp_recv->lock, flags);
out:
	deref_rmpp_recv(rmpp_recv);
	return done_wc;

drop3:	spin_unlock_irqrestore(&rmpp_recv->lock, flags);
drop2:	deref_rmpp_recv(rmpp_recv);
drop1:	ib_free_recv_mad(mad_recv_wc);
	return NULL;
}