#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {uintptr_t id; } ;
struct TYPE_13__ {TYPE_2__ release; } ;
struct xen_pvcalls_request {int req_id; TYPE_3__ u; int /*<<< orphan*/  cmd; } ;
struct socket {TYPE_1__* sk; } ;
struct TYPE_16__ {struct sock_mapping* accept_map; int /*<<< orphan*/  inflight_req_id; int /*<<< orphan*/  inflight_accept_req; } ;
struct TYPE_15__ {int /*<<< orphan*/  inflight_conn_req; TYPE_4__* ring; } ;
struct sock_mapping {TYPE_6__ passive; int /*<<< orphan*/  list; int /*<<< orphan*/  refcount; TYPE_5__ active; scalar_t__ active_socket; } ;
struct TYPE_19__ {int /*<<< orphan*/  req_prod_pvt; } ;
struct pvcalls_bedata {TYPE_7__* rsp; int /*<<< orphan*/  socket_lock; int /*<<< orphan*/  inflight_req; int /*<<< orphan*/  irq; TYPE_9__ ring; } ;
struct TYPE_18__ {int /*<<< orphan*/  dev; } ;
struct TYPE_17__ {int /*<<< orphan*/  req_id; } ;
struct TYPE_14__ {int /*<<< orphan*/  in_error; } ;
struct TYPE_11__ {int /*<<< orphan*/ * sk_send_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int EIO ; 
 int /*<<< orphan*/  ENOTCONN ; 
 scalar_t__ IS_ERR (struct sock_mapping*) ; 
 int /*<<< orphan*/  PTR_ERR (struct sock_mapping*) ; 
 scalar_t__ PVCALLS_INVALID_ID ; 
 int /*<<< orphan*/  PVCALLS_RELEASE ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 struct xen_pvcalls_request* RING_GET_REQUEST (TYPE_9__*,int) ; 
 int /*<<< orphan*/  RING_PUSH_REQUESTS_AND_CHECK_NOTIFY (TYPE_9__*,int) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,scalar_t__) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 struct pvcalls_bedata* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int get_request (struct pvcalls_bedata*,int*) ; 
 int /*<<< orphan*/  kfree (struct sock_mapping*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_remote_via_irq (int /*<<< orphan*/ ) ; 
 struct sock_mapping* pvcalls_enter_sock (struct socket*) ; 
 int /*<<< orphan*/  pvcalls_exit () ; 
 int /*<<< orphan*/  pvcalls_exit_sock (struct socket*) ; 
 TYPE_8__* pvcalls_front_dev ; 
 int /*<<< orphan*/  pvcalls_front_free_map (struct pvcalls_bedata*,struct sock_mapping*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

int pvcalls_front_release(struct socket *sock)
{
	struct pvcalls_bedata *bedata;
	struct sock_mapping *map;
	int req_id, notify, ret;
	struct xen_pvcalls_request *req;

	if (sock->sk == NULL)
		return 0;

	map = pvcalls_enter_sock(sock);
	if (IS_ERR(map)) {
		if (PTR_ERR(map) == -ENOTCONN)
			return -EIO;
		else
			return 0;
	}
	bedata = dev_get_drvdata(&pvcalls_front_dev->dev);

	spin_lock(&bedata->socket_lock);
	ret = get_request(bedata, &req_id);
	if (ret < 0) {
		spin_unlock(&bedata->socket_lock);
		pvcalls_exit_sock(sock);
		return ret;
	}
	sock->sk->sk_send_head = NULL;

	req = RING_GET_REQUEST(&bedata->ring, req_id);
	req->req_id = req_id;
	req->cmd = PVCALLS_RELEASE;
	req->u.release.id = (uintptr_t)map;

	bedata->ring.req_prod_pvt++;
	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&bedata->ring, notify);
	spin_unlock(&bedata->socket_lock);
	if (notify)
		notify_remote_via_irq(bedata->irq);

	wait_event(bedata->inflight_req,
		   READ_ONCE(bedata->rsp[req_id].req_id) == req_id);

	if (map->active_socket) {
		/*
		 * Set in_error and wake up inflight_conn_req to force
		 * recvmsg waiters to exit.
		 */
		map->active.ring->in_error = -EBADF;
		wake_up_interruptible(&map->active.inflight_conn_req);

		/*
		 * We need to make sure that sendmsg/recvmsg on this socket have
		 * not started before we've cleared sk_send_head here. The
		 * easiest way to guarantee this is to see that no pvcalls
		 * (other than us) is in progress on this socket.
		 */
		while (atomic_read(&map->refcount) > 1)
			cpu_relax();

		pvcalls_front_free_map(bedata, map);
	} else {
		wake_up(&bedata->inflight_req);
		wake_up(&map->passive.inflight_accept_req);

		while (atomic_read(&map->refcount) > 1)
			cpu_relax();

		spin_lock(&bedata->socket_lock);
		list_del(&map->list);
		spin_unlock(&bedata->socket_lock);
		if (READ_ONCE(map->passive.inflight_req_id) != PVCALLS_INVALID_ID &&
			READ_ONCE(map->passive.inflight_req_id) != 0) {
			pvcalls_front_free_map(bedata,
					       map->passive.accept_map);
		}
		kfree(map);
	}
	WRITE_ONCE(bedata->rsp[req_id].req_id, PVCALLS_INVALID_ID);

	pvcalls_exit();
	return 0;
}