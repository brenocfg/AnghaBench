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
struct ib_sa_query {int /*<<< orphan*/  (* release ) (struct ib_sa_query*) ;scalar_t__ client; int /*<<< orphan*/  id; int /*<<< orphan*/  (* callback ) (struct ib_sa_query*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct ib_mad_send_wc {int status; TYPE_1__* send_buf; } ;
struct ib_mad_agent {int dummy; } ;
struct TYPE_2__ {struct ib_sa_query** context; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
#define  IB_WC_RESP_TIMEOUT_ERR 130 
#define  IB_WC_SUCCESS 129 
#define  IB_WC_WR_FLUSH_ERR 128 
 int /*<<< orphan*/  __xa_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_mad (struct ib_sa_query*) ; 
 int /*<<< orphan*/  ib_sa_client_put (scalar_t__) ; 
 int /*<<< orphan*/  queries ; 
 int /*<<< orphan*/  stub1 (struct ib_sa_query*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct ib_sa_query*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (struct ib_sa_query*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (struct ib_sa_query*) ; 
 int /*<<< orphan*/  xa_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xa_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void send_handler(struct ib_mad_agent *agent,
			 struct ib_mad_send_wc *mad_send_wc)
{
	struct ib_sa_query *query = mad_send_wc->send_buf->context[0];
	unsigned long flags;

	if (query->callback)
		switch (mad_send_wc->status) {
		case IB_WC_SUCCESS:
			/* No callback -- already got recv */
			break;
		case IB_WC_RESP_TIMEOUT_ERR:
			query->callback(query, -ETIMEDOUT, NULL);
			break;
		case IB_WC_WR_FLUSH_ERR:
			query->callback(query, -EINTR, NULL);
			break;
		default:
			query->callback(query, -EIO, NULL);
			break;
		}

	xa_lock_irqsave(&queries, flags);
	__xa_erase(&queries, query->id);
	xa_unlock_irqrestore(&queries, flags);

	free_mad(query);
	if (query->client)
		ib_sa_client_put(query->client);
	query->release(query);
}