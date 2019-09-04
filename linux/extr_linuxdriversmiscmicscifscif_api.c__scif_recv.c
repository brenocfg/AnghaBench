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
struct scifmsg {int /*<<< orphan*/ * payload; int /*<<< orphan*/  uop; int /*<<< orphan*/  src; } ;
struct scif_qp {int /*<<< orphan*/  inbound_q; } ;
struct TYPE_2__ {struct scif_qp* qp; } ;
struct scif_endpt {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  recvwq; int /*<<< orphan*/  remote_dev; int /*<<< orphan*/  remote_ep; int /*<<< orphan*/  port; TYPE_1__ qp_info; } ;
typedef  scalar_t__ scif_epd_t ;

/* Variables and functions */
 int ECONNRESET ; 
 int ENOTCONN ; 
 scalar_t__ SCIFEP_CONNECTED ; 
 scalar_t__ SCIFEP_DISCONNECTED ; 
 int /*<<< orphan*/  SCIF_CLIENT_RCVD ; 
 int SCIF_ENDPT_QP_SIZE ; 
 int SCIF_RECV_BLOCK ; 
 int _scif_nodeqp_send (int /*<<< orphan*/ ,struct scifmsg*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int min (int,int) ; 
 int scif_rb_count (int /*<<< orphan*/ *,int) ; 
 int scif_rb_get_next (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  scif_rb_update_read_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int _scif_recv(scif_epd_t epd, void *msg, int len, int flags)
{
	int read_size;
	struct scif_endpt *ep = (struct scif_endpt *)epd;
	struct scifmsg notif_msg;
	int curr_recv_len = 0, remaining_len = len, read_count;
	int ret = 0;
	struct scif_qp *qp = ep->qp_info.qp;

	if (flags & SCIF_RECV_BLOCK)
		might_sleep();
	spin_lock(&ep->lock);
	while (remaining_len && (SCIFEP_CONNECTED == ep->state ||
				 SCIFEP_DISCONNECTED == ep->state)) {
		read_count = scif_rb_count(&qp->inbound_q, remaining_len);
		if (read_count) {
			/*
			 * Best effort to recv as much data as there
			 * are bytes to read in the RB particularly
			 * important for the Non Blocking case.
			 */
			curr_recv_len = min(remaining_len, read_count);
			read_size = scif_rb_get_next(&qp->inbound_q,
						     msg, curr_recv_len);
			if (ep->state == SCIFEP_CONNECTED) {
				/*
				 * Update the read pointer only if the endpoint
				 * is still connected else the read pointer
				 * might no longer exist since the peer has
				 * freed resources!
				 */
				scif_rb_update_read_ptr(&qp->inbound_q);
				/*
				 * Send a notification to the peer about the
				 * consumed data message only if the EP is in
				 * SCIFEP_CONNECTED state.
				 */
				notif_msg.src = ep->port;
				notif_msg.uop = SCIF_CLIENT_RCVD;
				notif_msg.payload[0] = ep->remote_ep;
				ret = _scif_nodeqp_send(ep->remote_dev,
							&notif_msg);
				if (ret)
					break;
			}
			remaining_len -= curr_recv_len;
			msg = msg + curr_recv_len;
			continue;
		}
		/*
		 * Bail out now if the EP is in SCIFEP_DISCONNECTED state else
		 * we will keep looping forever.
		 */
		if (ep->state == SCIFEP_DISCONNECTED)
			break;
		/*
		 * Return in the Non Blocking case if there is no data
		 * to read in this iteration.
		 */
		if (!(flags & SCIF_RECV_BLOCK))
			break;
		curr_recv_len = min(remaining_len, SCIF_ENDPT_QP_SIZE - 1);
		spin_unlock(&ep->lock);
		/*
		 * Wait for a SCIF_CLIENT_SEND message in the blocking case
		 * or until other side disconnects.
		 */
		ret =
		wait_event_interruptible(ep->recvwq,
					 SCIFEP_CONNECTED != ep->state ||
					 scif_rb_count(&qp->inbound_q,
						       curr_recv_len)
					 >= curr_recv_len);
		spin_lock(&ep->lock);
		if (ret)
			break;
	}
	if (len - remaining_len)
		ret = len - remaining_len;
	else if (!ret && ep->state != SCIFEP_CONNECTED)
		ret = ep->state == SCIFEP_DISCONNECTED ?
			-ECONNRESET : -ENOTCONN;
	spin_unlock(&ep->lock);
	return ret;
}