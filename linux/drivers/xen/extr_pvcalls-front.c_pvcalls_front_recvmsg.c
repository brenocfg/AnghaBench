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
struct socket {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  in_mutex; int /*<<< orphan*/  irq; int /*<<< orphan*/  data; int /*<<< orphan*/  ring; int /*<<< orphan*/  inflight_conn_req; } ;
struct sock_mapping {TYPE_1__ active; } ;
struct msghdr {int /*<<< orphan*/  msg_iter; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOTCONN ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct sock_mapping*) ; 
 int MSG_CMSG_CLOEXEC ; 
 int MSG_DONTWAIT ; 
 int MSG_ERRQUEUE ; 
 int MSG_OOB ; 
 int MSG_TRUNC ; 
 int PTR_ERR (struct sock_mapping*) ; 
 int /*<<< orphan*/  PVCALLS_RING_ORDER ; 
 size_t XEN_FLEX_RING_SIZE (int /*<<< orphan*/ ) ; 
 int __read_ring (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_remote_via_irq (int /*<<< orphan*/ ) ; 
 struct sock_mapping* pvcalls_enter_sock (struct socket*) ; 
 int /*<<< orphan*/  pvcalls_exit_sock (struct socket*) ; 
 int /*<<< orphan*/  pvcalls_front_read_todo (struct sock_mapping*) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pvcalls_front_recvmsg(struct socket *sock, struct msghdr *msg, size_t len,
		     int flags)
{
	int ret;
	struct sock_mapping *map;

	if (flags & (MSG_CMSG_CLOEXEC|MSG_ERRQUEUE|MSG_OOB|MSG_TRUNC))
		return -EOPNOTSUPP;

	map = pvcalls_enter_sock(sock);
	if (IS_ERR(map))
		return PTR_ERR(map);

	mutex_lock(&map->active.in_mutex);
	if (len > XEN_FLEX_RING_SIZE(PVCALLS_RING_ORDER))
		len = XEN_FLEX_RING_SIZE(PVCALLS_RING_ORDER);

	while (!(flags & MSG_DONTWAIT) && !pvcalls_front_read_todo(map)) {
		wait_event_interruptible(map->active.inflight_conn_req,
					 pvcalls_front_read_todo(map));
	}
	ret = __read_ring(map->active.ring, &map->active.data,
			  &msg->msg_iter, len, flags);

	if (ret > 0)
		notify_remote_via_irq(map->active.irq);
	if (ret == 0)
		ret = (flags & MSG_DONTWAIT) ? -EAGAIN : 0;
	if (ret == -ENOTCONN)
		ret = 0;

	mutex_unlock(&map->active.in_mutex);
	pvcalls_exit_sock(sock);
	return ret;
}