#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vhost_virtqueue {int num; TYPE_3__* heads; int /*<<< orphan*/  poll; } ;
struct vhost_net_virtqueue {size_t done_idx; struct vhost_virtqueue vq; } ;
struct vhost_net {int /*<<< orphan*/  dev; struct vhost_net_virtqueue* vqs; } ;
struct socket {TYPE_2__* ops; TYPE_1__* sk; } ;
struct msghdr {int /*<<< orphan*/  msg_flags; int /*<<< orphan*/ * msg_control; int /*<<< orphan*/  msg_iter; int /*<<< orphan*/  msg_controllen; int /*<<< orphan*/  msg_namelen; int /*<<< orphan*/ * msg_name; } ;
struct TYPE_6__ {scalar_t__ len; int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int (* sendmsg ) (struct socket*,struct msghdr*,size_t) ;} ;
struct TYPE_4__ {scalar_t__ sk_sndbuf; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 int /*<<< orphan*/  MSG_MORE ; 
 size_t VHOST_NET_BATCH ; 
 size_t VHOST_NET_VQ_TX ; 
 int /*<<< orphan*/  cpu_to_vhost32 (struct vhost_virtqueue*,int) ; 
 int get_tx_bufs (struct vhost_net*,struct vhost_net_virtqueue*,struct msghdr*,unsigned int*,unsigned int*,size_t*,int*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,size_t) ; 
 int stub1 (struct socket*,struct msghdr*,size_t) ; 
 scalar_t__ tx_can_batch (struct vhost_virtqueue*,size_t) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vhost_disable_notify (int /*<<< orphan*/ *,struct vhost_virtqueue*) ; 
 int /*<<< orphan*/  vhost_discard_vq_desc (struct vhost_virtqueue*,int) ; 
 int vhost_enable_notify (int /*<<< orphan*/ *,struct vhost_virtqueue*) ; 
 int /*<<< orphan*/  vhost_exceeds_weight (struct vhost_virtqueue*,int,size_t) ; 
 int vhost_net_build_xdp (struct vhost_net_virtqueue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_net_enable_vq (struct vhost_net*,struct vhost_virtqueue*) ; 
 int /*<<< orphan*/  vhost_poll_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_tx_batch (struct vhost_net*,struct vhost_net_virtqueue*,struct socket*,struct msghdr*) ; 

__attribute__((used)) static void handle_tx_copy(struct vhost_net *net, struct socket *sock)
{
	struct vhost_net_virtqueue *nvq = &net->vqs[VHOST_NET_VQ_TX];
	struct vhost_virtqueue *vq = &nvq->vq;
	unsigned out, in;
	int head;
	struct msghdr msg = {
		.msg_name = NULL,
		.msg_namelen = 0,
		.msg_control = NULL,
		.msg_controllen = 0,
		.msg_flags = MSG_DONTWAIT,
	};
	size_t len, total_len = 0;
	int err;
	int sent_pkts = 0;
	bool sock_can_batch = (sock->sk->sk_sndbuf == INT_MAX);

	do {
		bool busyloop_intr = false;

		if (nvq->done_idx == VHOST_NET_BATCH)
			vhost_tx_batch(net, nvq, sock, &msg);

		head = get_tx_bufs(net, nvq, &msg, &out, &in, &len,
				   &busyloop_intr);
		/* On error, stop handling until the next kick. */
		if (unlikely(head < 0))
			break;
		/* Nothing new?  Wait for eventfd to tell us they refilled. */
		if (head == vq->num) {
			if (unlikely(busyloop_intr)) {
				vhost_poll_queue(&vq->poll);
			} else if (unlikely(vhost_enable_notify(&net->dev,
								vq))) {
				vhost_disable_notify(&net->dev, vq);
				continue;
			}
			break;
		}

		total_len += len;

		/* For simplicity, TX batching is only enabled if
		 * sndbuf is unlimited.
		 */
		if (sock_can_batch) {
			err = vhost_net_build_xdp(nvq, &msg.msg_iter);
			if (!err) {
				goto done;
			} else if (unlikely(err != -ENOSPC)) {
				vhost_tx_batch(net, nvq, sock, &msg);
				vhost_discard_vq_desc(vq, 1);
				vhost_net_enable_vq(net, vq);
				break;
			}

			/* We can't build XDP buff, go for single
			 * packet path but let's flush batched
			 * packets.
			 */
			vhost_tx_batch(net, nvq, sock, &msg);
			msg.msg_control = NULL;
		} else {
			if (tx_can_batch(vq, total_len))
				msg.msg_flags |= MSG_MORE;
			else
				msg.msg_flags &= ~MSG_MORE;
		}

		/* TODO: Check specific error and bomb out unless ENOBUFS? */
		err = sock->ops->sendmsg(sock, &msg, len);
		if (unlikely(err < 0)) {
			vhost_discard_vq_desc(vq, 1);
			vhost_net_enable_vq(net, vq);
			break;
		}
		if (err != len)
			pr_debug("Truncated TX packet: len %d != %zd\n",
				 err, len);
done:
		vq->heads[nvq->done_idx].id = cpu_to_vhost32(vq, head);
		vq->heads[nvq->done_idx].len = 0;
		++nvq->done_idx;
	} while (likely(!vhost_exceeds_weight(vq, ++sent_pkts, total_len)));

	vhost_tx_batch(net, nvq, sock, &msg);
}