#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {uintptr_t id; uintptr_t id_new; int evtchn; int /*<<< orphan*/  ref; } ;
struct TYPE_13__ {TYPE_2__ accept; } ;
struct xen_pvcalls_request {int req_id; TYPE_3__ u; int /*<<< orphan*/  cmd; } ;
struct socket {TYPE_6__* sk; } ;
struct TYPE_14__ {scalar_t__ status; int inflight_req_id; int /*<<< orphan*/  inflight_accept_req; int /*<<< orphan*/  flags; struct sock_mapping* accept_map; } ;
struct TYPE_11__ {int /*<<< orphan*/  ref; } ;
struct sock_mapping {TYPE_4__ passive; struct socket* sock; TYPE_1__ active; int /*<<< orphan*/  list; } ;
struct TYPE_18__ {int /*<<< orphan*/  req_prod_pvt; } ;
struct pvcalls_bedata {TYPE_5__* rsp; int /*<<< orphan*/  inflight_req; int /*<<< orphan*/  irq; int /*<<< orphan*/  socket_lock; TYPE_9__ ring; int /*<<< orphan*/  socket_mappings; } ;
struct TYPE_17__ {int /*<<< orphan*/  dev; } ;
struct TYPE_16__ {void* sk_send_head; } ;
struct TYPE_15__ {int req_id; int ret; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINTR ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct sock_mapping*) ; 
 int /*<<< orphan*/  PF_INET ; 
 int PTR_ERR (struct sock_mapping*) ; 
 int /*<<< orphan*/  PVCALLS_ACCEPT ; 
 int /*<<< orphan*/  PVCALLS_FLAG_ACCEPT_INFLIGHT ; 
 int PVCALLS_INVALID_ID ; 
 scalar_t__ PVCALLS_STATUS_LISTEN ; 
 int READ_ONCE (int) ; 
 struct xen_pvcalls_request* RING_GET_REQUEST (TYPE_9__*,int) ; 
 int /*<<< orphan*/  RING_PUSH_REQUESTS_AND_CHECK_NOTIFY (TYPE_9__*,int) ; 
 int SOCK_NONBLOCK ; 
 int /*<<< orphan*/  WRITE_ONCE (int,int) ; 
 int alloc_active_ring (struct sock_mapping*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,void*) ; 
 int create_active (struct sock_mapping*,int*) ; 
 struct pvcalls_bedata* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_active_ring (struct sock_mapping*) ; 
 int get_request (struct pvcalls_bedata*,int*) ; 
 int /*<<< orphan*/  kfree (struct sock_mapping*) ; 
 struct sock_mapping* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_remote_via_irq (int /*<<< orphan*/ ) ; 
 struct sock_mapping* pvcalls_enter_sock (struct socket*) ; 
 int /*<<< orphan*/  pvcalls_exit_sock (struct socket*) ; 
 TYPE_8__* pvcalls_front_dev ; 
 int /*<<< orphan*/  pvcalls_front_free_map (struct pvcalls_bedata*,struct sock_mapping*) ; 
 int /*<<< orphan*/  pvcalls_proto ; 
 TYPE_6__* sk_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  sock_net (TYPE_6__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ wait_event_interruptible (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int pvcalls_front_accept(struct socket *sock, struct socket *newsock, int flags)
{
	struct pvcalls_bedata *bedata;
	struct sock_mapping *map;
	struct sock_mapping *map2 = NULL;
	struct xen_pvcalls_request *req;
	int notify, req_id, ret, evtchn, nonblock;

	map = pvcalls_enter_sock(sock);
	if (IS_ERR(map))
		return PTR_ERR(map);
	bedata = dev_get_drvdata(&pvcalls_front_dev->dev);

	if (map->passive.status != PVCALLS_STATUS_LISTEN) {
		pvcalls_exit_sock(sock);
		return -EINVAL;
	}

	nonblock = flags & SOCK_NONBLOCK;
	/*
	 * Backend only supports 1 inflight accept request, will return
	 * errors for the others
	 */
	if (test_and_set_bit(PVCALLS_FLAG_ACCEPT_INFLIGHT,
			     (void *)&map->passive.flags)) {
		req_id = READ_ONCE(map->passive.inflight_req_id);
		if (req_id != PVCALLS_INVALID_ID &&
		    READ_ONCE(bedata->rsp[req_id].req_id) == req_id) {
			map2 = map->passive.accept_map;
			goto received;
		}
		if (nonblock) {
			pvcalls_exit_sock(sock);
			return -EAGAIN;
		}
		if (wait_event_interruptible(map->passive.inflight_accept_req,
			!test_and_set_bit(PVCALLS_FLAG_ACCEPT_INFLIGHT,
					  (void *)&map->passive.flags))) {
			pvcalls_exit_sock(sock);
			return -EINTR;
		}
	}

	map2 = kzalloc(sizeof(*map2), GFP_KERNEL);
	if (map2 == NULL) {
		clear_bit(PVCALLS_FLAG_ACCEPT_INFLIGHT,
			  (void *)&map->passive.flags);
		pvcalls_exit_sock(sock);
		return -ENOMEM;
	}
	ret = alloc_active_ring(map2);
	if (ret < 0) {
		clear_bit(PVCALLS_FLAG_ACCEPT_INFLIGHT,
				(void *)&map->passive.flags);
		kfree(map2);
		pvcalls_exit_sock(sock);
		return ret;
	}
	spin_lock(&bedata->socket_lock);
	ret = get_request(bedata, &req_id);
	if (ret < 0) {
		clear_bit(PVCALLS_FLAG_ACCEPT_INFLIGHT,
			  (void *)&map->passive.flags);
		spin_unlock(&bedata->socket_lock);
		free_active_ring(map2);
		kfree(map2);
		pvcalls_exit_sock(sock);
		return ret;
	}

	ret = create_active(map2, &evtchn);
	if (ret < 0) {
		free_active_ring(map2);
		kfree(map2);
		clear_bit(PVCALLS_FLAG_ACCEPT_INFLIGHT,
			  (void *)&map->passive.flags);
		spin_unlock(&bedata->socket_lock);
		pvcalls_exit_sock(sock);
		return ret;
	}
	list_add_tail(&map2->list, &bedata->socket_mappings);

	req = RING_GET_REQUEST(&bedata->ring, req_id);
	req->req_id = req_id;
	req->cmd = PVCALLS_ACCEPT;
	req->u.accept.id = (uintptr_t) map;
	req->u.accept.ref = map2->active.ref;
	req->u.accept.id_new = (uintptr_t) map2;
	req->u.accept.evtchn = evtchn;
	map->passive.accept_map = map2;

	bedata->ring.req_prod_pvt++;
	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&bedata->ring, notify);
	spin_unlock(&bedata->socket_lock);
	if (notify)
		notify_remote_via_irq(bedata->irq);
	/* We could check if we have received a response before returning. */
	if (nonblock) {
		WRITE_ONCE(map->passive.inflight_req_id, req_id);
		pvcalls_exit_sock(sock);
		return -EAGAIN;
	}

	if (wait_event_interruptible(bedata->inflight_req,
		READ_ONCE(bedata->rsp[req_id].req_id) == req_id)) {
		pvcalls_exit_sock(sock);
		return -EINTR;
	}
	/* read req_id, then the content */
	smp_rmb();

received:
	map2->sock = newsock;
	newsock->sk = sk_alloc(sock_net(sock->sk), PF_INET, GFP_KERNEL, &pvcalls_proto, false);
	if (!newsock->sk) {
		bedata->rsp[req_id].req_id = PVCALLS_INVALID_ID;
		map->passive.inflight_req_id = PVCALLS_INVALID_ID;
		clear_bit(PVCALLS_FLAG_ACCEPT_INFLIGHT,
			  (void *)&map->passive.flags);
		pvcalls_front_free_map(bedata, map2);
		pvcalls_exit_sock(sock);
		return -ENOMEM;
	}
	newsock->sk->sk_send_head = (void *)map2;

	ret = bedata->rsp[req_id].ret;
	bedata->rsp[req_id].req_id = PVCALLS_INVALID_ID;
	map->passive.inflight_req_id = PVCALLS_INVALID_ID;

	clear_bit(PVCALLS_FLAG_ACCEPT_INFLIGHT, (void *)&map->passive.flags);
	wake_up(&map->passive.inflight_accept_req);

	pvcalls_exit_sock(sock);
	return ret;
}