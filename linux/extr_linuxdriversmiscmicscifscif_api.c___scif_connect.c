#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct scif_port_id {size_t node; } ;
struct TYPE_9__ {TYPE_3__* qp; } ;
struct TYPE_7__ {int port; int /*<<< orphan*/  node; } ;
struct scif_endpt {size_t state; scalar_t__ conn_async_state; int conn_err; int /*<<< orphan*/  lock; int /*<<< orphan*/  conn_list; int /*<<< orphan*/  conn_pend_wq; TYPE_4__ qp_info; struct scif_dev* remote_dev; int /*<<< orphan*/  conwq; int /*<<< orphan*/  recvwq; int /*<<< orphan*/  sendwq; struct scif_port_id conn_port; TYPE_2__ port; } ;
struct scif_dev {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ scif_epd_t ;
struct TYPE_6__ {int /*<<< orphan*/  this_device; } ;
struct TYPE_10__ {size_t maxid; int /*<<< orphan*/  conn_work; int /*<<< orphan*/  nb_connect_lock; int /*<<< orphan*/  nb_connect_list; int /*<<< orphan*/  nodeid; TYPE_1__ mdev; } ;
struct TYPE_8__ {int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 scalar_t__ ASYNC_CONN_FLUSH_WORK ; 
 void* ASYNC_CONN_IDLE ; 
 scalar_t__ ASYNC_CONN_INPROGRESS ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int EISCONN ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int PTR_ERR (struct device*) ; 
#define  SCIFEP_BOUND 137 
#define  SCIFEP_CLLISTEN 136 
#define  SCIFEP_CLOSING 135 
#define  SCIFEP_CONNECTED 134 
#define  SCIFEP_CONNECTING 133 
#define  SCIFEP_DISCONNECTED 132 
#define  SCIFEP_LISTENING 131 
 int /*<<< orphan*/  SCIFEP_MAGIC ; 
#define  SCIFEP_MAPPING 130 
#define  SCIFEP_UNBOUND 129 
#define  SCIFEP_ZOMBIE 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct scif_endpt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int scif_conn_func (struct scif_endpt*) ; 
 struct scif_dev* scif_dev ; 
 int /*<<< orphan*/ * scif_ep_states ; 
 int scif_get_new_port () ; 
 struct device* scif_get_peer_dev (struct scif_dev*) ; 
 TYPE_5__ scif_info ; 
 int /*<<< orphan*/  scif_put_peer_dev (struct device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlikely (int) ; 

int __scif_connect(scif_epd_t epd, struct scif_port_id *dst, bool non_block)
{
	struct scif_endpt *ep = (struct scif_endpt *)epd;
	int err = 0;
	struct scif_dev *remote_dev;
	struct device *spdev;

	dev_dbg(scif_info.mdev.this_device, "SCIFAPI connect: ep %p %s\n", ep,
		scif_ep_states[ep->state]);

	if (!scif_dev || dst->node > scif_info.maxid)
		return -ENODEV;

	might_sleep();

	remote_dev = &scif_dev[dst->node];
	spdev = scif_get_peer_dev(remote_dev);
	if (IS_ERR(spdev)) {
		err = PTR_ERR(spdev);
		return err;
	}

	spin_lock(&ep->lock);
	switch (ep->state) {
	case SCIFEP_ZOMBIE:
	case SCIFEP_CLOSING:
		err = -EINVAL;
		break;
	case SCIFEP_DISCONNECTED:
		if (ep->conn_async_state == ASYNC_CONN_INPROGRESS)
			ep->conn_async_state = ASYNC_CONN_FLUSH_WORK;
		else
			err = -EINVAL;
		break;
	case SCIFEP_LISTENING:
	case SCIFEP_CLLISTEN:
		err = -EOPNOTSUPP;
		break;
	case SCIFEP_CONNECTING:
	case SCIFEP_MAPPING:
		if (ep->conn_async_state == ASYNC_CONN_INPROGRESS)
			err = -EINPROGRESS;
		else
			err = -EISCONN;
		break;
	case SCIFEP_CONNECTED:
		if (ep->conn_async_state == ASYNC_CONN_INPROGRESS)
			ep->conn_async_state = ASYNC_CONN_FLUSH_WORK;
		else
			err = -EISCONN;
		break;
	case SCIFEP_UNBOUND:
		err = scif_get_new_port();
		if (err < 0)
			break;
		ep->port.port = err;
		ep->port.node = scif_info.nodeid;
		ep->conn_async_state = ASYNC_CONN_IDLE;
		/* Fall through */
	case SCIFEP_BOUND:
		/*
		 * If a non-blocking connect has been already initiated
		 * (conn_async_state is either ASYNC_CONN_INPROGRESS or
		 * ASYNC_CONN_FLUSH_WORK), the end point could end up in
		 * SCIF_BOUND due an error in the connection process
		 * (e.g., connection refused) If conn_async_state is
		 * ASYNC_CONN_INPROGRESS - transition to ASYNC_CONN_FLUSH_WORK
		 * so that the error status can be collected. If the state is
		 * already ASYNC_CONN_FLUSH_WORK - then set the error to
		 * EINPROGRESS since some other thread is waiting to collect
		 * error status.
		 */
		if (ep->conn_async_state == ASYNC_CONN_INPROGRESS) {
			ep->conn_async_state = ASYNC_CONN_FLUSH_WORK;
		} else if (ep->conn_async_state == ASYNC_CONN_FLUSH_WORK) {
			err = -EINPROGRESS;
		} else {
			ep->conn_port = *dst;
			init_waitqueue_head(&ep->sendwq);
			init_waitqueue_head(&ep->recvwq);
			init_waitqueue_head(&ep->conwq);
			ep->conn_async_state = 0;

			if (unlikely(non_block))
				ep->conn_async_state = ASYNC_CONN_INPROGRESS;
		}
		break;
	}

	if (err || ep->conn_async_state == ASYNC_CONN_FLUSH_WORK)
			goto connect_simple_unlock1;

	ep->state = SCIFEP_CONNECTING;
	ep->remote_dev = &scif_dev[dst->node];
	ep->qp_info.qp->magic = SCIFEP_MAGIC;
	if (ep->conn_async_state == ASYNC_CONN_INPROGRESS) {
		init_waitqueue_head(&ep->conn_pend_wq);
		spin_lock(&scif_info.nb_connect_lock);
		list_add_tail(&ep->conn_list, &scif_info.nb_connect_list);
		spin_unlock(&scif_info.nb_connect_lock);
		err = -EINPROGRESS;
		schedule_work(&scif_info.conn_work);
	}
connect_simple_unlock1:
	spin_unlock(&ep->lock);
	scif_put_peer_dev(spdev);
	if (err) {
		return err;
	} else if (ep->conn_async_state == ASYNC_CONN_FLUSH_WORK) {
		flush_work(&scif_info.conn_work);
		err = ep->conn_err;
		spin_lock(&ep->lock);
		ep->conn_async_state = ASYNC_CONN_IDLE;
		spin_unlock(&ep->lock);
	} else {
		err = scif_conn_func(ep);
	}
	return err;
}