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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {scalar_t__ seg_count; } ;
struct ib_mad_send_wr_private {scalar_t__ last_ack; scalar_t__ status; TYPE_1__ send_buf; int /*<<< orphan*/  timeout; } ;
struct ib_mad_send_wc {TYPE_1__* send_buf; int /*<<< orphan*/  vendor_err; int /*<<< orphan*/  status; } ;
struct ib_mad_recv_wc {int dummy; } ;
struct ib_mad_agent_private {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WC_REM_ABORT_ERR ; 
 scalar_t__ IB_WC_SUCCESS ; 
 struct ib_mad_send_wr_private* ib_find_send_mad (struct ib_mad_agent_private*,struct ib_mad_recv_wc*) ; 
 int /*<<< orphan*/  ib_mad_complete_send_wr (struct ib_mad_send_wr_private*,struct ib_mad_send_wc*) ; 
 int /*<<< orphan*/  ib_mark_mad_done (struct ib_mad_send_wr_private*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void abort_send(struct ib_mad_agent_private *agent,
		       struct ib_mad_recv_wc *mad_recv_wc, u8 rmpp_status)
{
	struct ib_mad_send_wr_private *mad_send_wr;
	struct ib_mad_send_wc wc;
	unsigned long flags;

	spin_lock_irqsave(&agent->lock, flags);
	mad_send_wr = ib_find_send_mad(agent, mad_recv_wc);
	if (!mad_send_wr)
		goto out;	/* Unmatched send */

	if ((mad_send_wr->last_ack == mad_send_wr->send_buf.seg_count) ||
	    (!mad_send_wr->timeout) || (mad_send_wr->status != IB_WC_SUCCESS))
		goto out;	/* Send is already done */

	ib_mark_mad_done(mad_send_wr);
	spin_unlock_irqrestore(&agent->lock, flags);

	wc.status = IB_WC_REM_ABORT_ERR;
	wc.vendor_err = rmpp_status;
	wc.send_buf = &mad_send_wr->send_buf;
	ib_mad_complete_send_wr(mad_send_wr, &wc);
	return;
out:
	spin_unlock_irqrestore(&agent->lock, flags);
}