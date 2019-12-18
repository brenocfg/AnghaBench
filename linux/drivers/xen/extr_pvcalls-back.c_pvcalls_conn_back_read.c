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
struct pvcalls_data {scalar_t__ in; } ;
struct sock_mapping {int /*<<< orphan*/  irq; int /*<<< orphan*/  read; TYPE_3__* sock; int /*<<< orphan*/  ring_order; struct pvcalls_data data; struct pvcalls_data_intf* ring; } ;
struct pvcalls_data_intf {scalar_t__ in_cons; scalar_t__ in_prod; int in_error; } ;
struct msghdr {int /*<<< orphan*/  msg_iter; } ;
struct kvec {scalar_t__ iov_base; scalar_t__ iov_len; } ;
typedef  int /*<<< orphan*/  msg ;
typedef  int int32_t ;
struct TYPE_6__ {TYPE_1__* sk; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {TYPE_2__ sk_receive_queue; } ;
typedef  scalar_t__ RING_IDX ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WRITE ; 
 scalar_t__ XEN_FLEX_RING_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int inet_recvmsg (TYPE_3__*,struct msghdr*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iov_iter_kvec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kvec*,int,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct msghdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  notify_remote_via_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ pvcalls_mask (scalar_t__,scalar_t__) ; 
 scalar_t__ pvcalls_queued (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ skb_queue_empty (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  virt_mb () ; 
 int /*<<< orphan*/  virt_wmb () ; 

__attribute__((used)) static void pvcalls_conn_back_read(void *opaque)
{
	struct sock_mapping *map = (struct sock_mapping *)opaque;
	struct msghdr msg;
	struct kvec vec[2];
	RING_IDX cons, prod, size, wanted, array_size, masked_prod, masked_cons;
	int32_t error;
	struct pvcalls_data_intf *intf = map->ring;
	struct pvcalls_data *data = &map->data;
	unsigned long flags;
	int ret;

	array_size = XEN_FLEX_RING_SIZE(map->ring_order);
	cons = intf->in_cons;
	prod = intf->in_prod;
	error = intf->in_error;
	/* read the indexes first, then deal with the data */
	virt_mb();

	if (error)
		return;

	size = pvcalls_queued(prod, cons, array_size);
	if (size >= array_size)
		return;
	spin_lock_irqsave(&map->sock->sk->sk_receive_queue.lock, flags);
	if (skb_queue_empty(&map->sock->sk->sk_receive_queue)) {
		atomic_set(&map->read, 0);
		spin_unlock_irqrestore(&map->sock->sk->sk_receive_queue.lock,
				flags);
		return;
	}
	spin_unlock_irqrestore(&map->sock->sk->sk_receive_queue.lock, flags);
	wanted = array_size - size;
	masked_prod = pvcalls_mask(prod, array_size);
	masked_cons = pvcalls_mask(cons, array_size);

	memset(&msg, 0, sizeof(msg));
	if (masked_prod < masked_cons) {
		vec[0].iov_base = data->in + masked_prod;
		vec[0].iov_len = wanted;
		iov_iter_kvec(&msg.msg_iter, WRITE, vec, 1, wanted);
	} else {
		vec[0].iov_base = data->in + masked_prod;
		vec[0].iov_len = array_size - masked_prod;
		vec[1].iov_base = data->in;
		vec[1].iov_len = wanted - vec[0].iov_len;
		iov_iter_kvec(&msg.msg_iter, WRITE, vec, 2, wanted);
	}

	atomic_set(&map->read, 0);
	ret = inet_recvmsg(map->sock, &msg, wanted, MSG_DONTWAIT);
	WARN_ON(ret > wanted);
	if (ret == -EAGAIN) /* shouldn't happen */
		return;
	if (!ret)
		ret = -ENOTCONN;
	spin_lock_irqsave(&map->sock->sk->sk_receive_queue.lock, flags);
	if (ret > 0 && !skb_queue_empty(&map->sock->sk->sk_receive_queue))
		atomic_inc(&map->read);
	spin_unlock_irqrestore(&map->sock->sk->sk_receive_queue.lock, flags);

	/* write the data, then modify the indexes */
	virt_wmb();
	if (ret < 0) {
		atomic_set(&map->read, 0);
		intf->in_error = ret;
	} else
		intf->in_prod = prod + ret;
	/* update the indexes, then notify the other end */
	virt_wmb();
	notify_remote_via_irq(map->irq);

	return;
}