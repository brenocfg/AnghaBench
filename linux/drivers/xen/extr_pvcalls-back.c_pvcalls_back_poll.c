#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct xenbus_device {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
struct TYPE_9__ {TYPE_2__ poll; } ;
struct xen_pvcalls_response {scalar_t__ cmd; int ret; TYPE_3__ u; int /*<<< orphan*/  req_id; } ;
struct TYPE_10__ {int /*<<< orphan*/  id; } ;
struct TYPE_11__ {TYPE_4__ poll; } ;
struct xen_pvcalls_request {scalar_t__ cmd; TYPE_5__ u; int /*<<< orphan*/  req_id; } ;
struct sockpass_mapping {int /*<<< orphan*/  copy_lock; struct xen_pvcalls_request reqcopy; TYPE_1__* sock; } ;
struct request_sock_queue {int /*<<< orphan*/  rskq_accept_head; } ;
struct TYPE_12__ {int /*<<< orphan*/  rsp_prod_pvt; } ;
struct pvcalls_fedata {TYPE_6__ ring; int /*<<< orphan*/  socket_lock; int /*<<< orphan*/  socketpass_mappings; } ;
struct inet_connection_sock {struct request_sock_queue icsk_accept_queue; } ;
struct TYPE_7__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int EINTR ; 
 int EINVAL ; 
 int /*<<< orphan*/ * READ_ONCE (int /*<<< orphan*/ ) ; 
 struct xen_pvcalls_response* RING_GET_RESPONSE (TYPE_6__*,int /*<<< orphan*/ ) ; 
 struct pvcalls_fedata* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 struct inet_connection_sock* inet_csk (int /*<<< orphan*/ ) ; 
 struct sockpass_mapping* radix_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pvcalls_back_poll(struct xenbus_device *dev,
			     struct xen_pvcalls_request *req)
{
	struct pvcalls_fedata *fedata;
	struct sockpass_mapping *mappass;
	struct xen_pvcalls_response *rsp;
	struct inet_connection_sock *icsk;
	struct request_sock_queue *queue;
	unsigned long flags;
	int ret;
	bool data;

	fedata = dev_get_drvdata(&dev->dev);

	down(&fedata->socket_lock);
	mappass = radix_tree_lookup(&fedata->socketpass_mappings,
				    req->u.poll.id);
	up(&fedata->socket_lock);
	if (mappass == NULL)
		return -EINVAL;

	/*
	 * Limitation of the current implementation: only support one
	 * concurrent accept or poll call on one socket.
	 */
	spin_lock_irqsave(&mappass->copy_lock, flags);
	if (mappass->reqcopy.cmd != 0) {
		ret = -EINTR;
		goto out;
	}

	mappass->reqcopy = *req;
	icsk = inet_csk(mappass->sock->sk);
	queue = &icsk->icsk_accept_queue;
	data = READ_ONCE(queue->rskq_accept_head) != NULL;
	if (data) {
		mappass->reqcopy.cmd = 0;
		ret = 0;
		goto out;
	}
	spin_unlock_irqrestore(&mappass->copy_lock, flags);

	/* Tell the caller we don't need to send back a notification yet */
	return -1;

out:
	spin_unlock_irqrestore(&mappass->copy_lock, flags);

	rsp = RING_GET_RESPONSE(&fedata->ring, fedata->ring.rsp_prod_pvt++);
	rsp->req_id = req->req_id;
	rsp->cmd = req->cmd;
	rsp->u.poll.id = req->u.poll.id;
	rsp->ret = ret;
	return 0;
}