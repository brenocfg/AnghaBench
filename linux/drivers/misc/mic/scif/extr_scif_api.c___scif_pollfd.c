#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* qp; } ;
struct scif_endpt {size_t state; scalar_t__ conn_async_state; int /*<<< orphan*/  lock; TYPE_3__ qp_info; int /*<<< orphan*/  sendwq; int /*<<< orphan*/  recvwq; scalar_t__ conreqcnt; int /*<<< orphan*/  conwq; scalar_t__ conn_err; int /*<<< orphan*/  conn_pend_wq; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_5__ {int /*<<< orphan*/  this_device; } ;
struct TYPE_8__ {TYPE_1__ mdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  outbound_q; int /*<<< orphan*/  inbound_q; } ;

/* Variables and functions */
 scalar_t__ ASYNC_CONN_INPROGRESS ; 
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 size_t SCIFEP_CONNECTED ; 
 size_t SCIFEP_DISCONNECTED ; 
 size_t SCIFEP_LISTENING ; 
 int /*<<< orphan*/  _scif_poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct scif_endpt*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct scif_endpt*,int /*<<< orphan*/ ) ; 
 int poll_requested_events (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * scif_ep_states ; 
 TYPE_4__ scif_info ; 
 scalar_t__ scif_rb_count (int /*<<< orphan*/ *,int) ; 
 scalar_t__ scif_rb_space (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__poll_t
__scif_pollfd(struct file *f, poll_table *wait, struct scif_endpt *ep)
{
	__poll_t mask = 0;

	dev_dbg(scif_info.mdev.this_device,
		"SCIFAPI pollfd: ep %p %s\n", ep, scif_ep_states[ep->state]);

	spin_lock(&ep->lock);

	/* Endpoint is waiting for a non-blocking connect to complete */
	if (ep->conn_async_state == ASYNC_CONN_INPROGRESS) {
		_scif_poll_wait(f, &ep->conn_pend_wq, wait, ep);
		if (ep->conn_async_state == ASYNC_CONN_INPROGRESS) {
			if (ep->state == SCIFEP_CONNECTED ||
			    ep->state == SCIFEP_DISCONNECTED ||
			    ep->conn_err)
				mask |= EPOLLOUT;
			goto exit;
		}
	}

	/* Endpoint is listening for incoming connection requests */
	if (ep->state == SCIFEP_LISTENING) {
		_scif_poll_wait(f, &ep->conwq, wait, ep);
		if (ep->state == SCIFEP_LISTENING) {
			if (ep->conreqcnt)
				mask |= EPOLLIN;
			goto exit;
		}
	}

	/* Endpoint is connected or disconnected */
	if (ep->state == SCIFEP_CONNECTED || ep->state == SCIFEP_DISCONNECTED) {
		if (poll_requested_events(wait) & EPOLLIN)
			_scif_poll_wait(f, &ep->recvwq, wait, ep);
		if (poll_requested_events(wait) & EPOLLOUT)
			_scif_poll_wait(f, &ep->sendwq, wait, ep);
		if (ep->state == SCIFEP_CONNECTED ||
		    ep->state == SCIFEP_DISCONNECTED) {
			/* Data can be read without blocking */
			if (scif_rb_count(&ep->qp_info.qp->inbound_q, 1))
				mask |= EPOLLIN;
			/* Data can be written without blocking */
			if (scif_rb_space(&ep->qp_info.qp->outbound_q))
				mask |= EPOLLOUT;
			/* Return EPOLLHUP if endpoint is disconnected */
			if (ep->state == SCIFEP_DISCONNECTED)
				mask |= EPOLLHUP;
			goto exit;
		}
	}

	/* Return EPOLLERR if the endpoint is in none of the above states */
	mask |= EPOLLERR;
exit:
	spin_unlock(&ep->lock);
	return mask;
}