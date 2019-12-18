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
struct ib_sa_query {struct ib_mad_send_buf* mad_buf; TYPE_1__* port; } ;
struct ib_mad_send_buf {int dummy; } ;
struct ib_mad_agent {int dummy; } ;
struct TYPE_2__ {struct ib_mad_agent* agent; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_cancel_mad (struct ib_mad_agent*,struct ib_mad_send_buf*) ; 
 int /*<<< orphan*/  ib_nl_cancel_request (struct ib_sa_query*) ; 
 int /*<<< orphan*/  queries ; 
 struct ib_sa_query* xa_load (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xa_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xa_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ib_sa_cancel_query(int id, struct ib_sa_query *query)
{
	unsigned long flags;
	struct ib_mad_agent *agent;
	struct ib_mad_send_buf *mad_buf;

	xa_lock_irqsave(&queries, flags);
	if (xa_load(&queries, id) != query) {
		xa_unlock_irqrestore(&queries, flags);
		return;
	}
	agent = query->port->agent;
	mad_buf = query->mad_buf;
	xa_unlock_irqrestore(&queries, flags);

	/*
	 * If the query is still on the netlink request list, schedule
	 * it to be cancelled by the timeout routine. Otherwise, it has been
	 * sent to the MAD layer and has to be cancelled from there.
	 */
	if (!ib_nl_cancel_request(query))
		ib_cancel_mad(agent, mad_buf);
}