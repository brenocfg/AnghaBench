#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pvcalls_data {int out; } ;
struct sock_mapping {int /*<<< orphan*/  irq; int /*<<< orphan*/  write; int /*<<< orphan*/  io; int /*<<< orphan*/  sock; int /*<<< orphan*/  ring_order; struct pvcalls_data data; struct pvcalls_data_intf* ring; } ;
struct pvcalls_data_intf {int out_cons; int out_prod; int out_error; } ;
struct msghdr {int /*<<< orphan*/  msg_iter; int /*<<< orphan*/  msg_flags; } ;
struct kvec {int iov_base; int iov_len; } ;
typedef  int /*<<< orphan*/  msg ;
typedef  int RING_IDX ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 int /*<<< orphan*/  READ ; 
 int XEN_FLEX_RING_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int inet_sendmsg (int /*<<< orphan*/ ,struct msghdr*,int) ; 
 int /*<<< orphan*/  iov_iter_kvec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kvec*,int,int) ; 
 int /*<<< orphan*/  memset (struct msghdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  notify_remote_via_irq (int /*<<< orphan*/ ) ; 
 int pvcalls_mask (int,int) ; 
 int pvcalls_queued (int,int,int) ; 
 int /*<<< orphan*/  virt_mb () ; 
 int /*<<< orphan*/  virt_wmb () ; 

__attribute__((used)) static void pvcalls_conn_back_write(struct sock_mapping *map)
{
	struct pvcalls_data_intf *intf = map->ring;
	struct pvcalls_data *data = &map->data;
	struct msghdr msg;
	struct kvec vec[2];
	RING_IDX cons, prod, size, array_size;
	int ret;

	cons = intf->out_cons;
	prod = intf->out_prod;
	/* read the indexes before dealing with the data */
	virt_mb();

	array_size = XEN_FLEX_RING_SIZE(map->ring_order);
	size = pvcalls_queued(prod, cons, array_size);
	if (size == 0)
		return;

	memset(&msg, 0, sizeof(msg));
	msg.msg_flags |= MSG_DONTWAIT;
	if (pvcalls_mask(prod, array_size) > pvcalls_mask(cons, array_size)) {
		vec[0].iov_base = data->out + pvcalls_mask(cons, array_size);
		vec[0].iov_len = size;
		iov_iter_kvec(&msg.msg_iter, READ, vec, 1, size);
	} else {
		vec[0].iov_base = data->out + pvcalls_mask(cons, array_size);
		vec[0].iov_len = array_size - pvcalls_mask(cons, array_size);
		vec[1].iov_base = data->out;
		vec[1].iov_len = size - vec[0].iov_len;
		iov_iter_kvec(&msg.msg_iter, READ, vec, 2, size);
	}

	atomic_set(&map->write, 0);
	ret = inet_sendmsg(map->sock, &msg, size);
	if (ret == -EAGAIN || (ret >= 0 && ret < size)) {
		atomic_inc(&map->write);
		atomic_inc(&map->io);
	}
	if (ret == -EAGAIN)
		return;

	/* write the data, then update the indexes */
	virt_wmb();
	if (ret < 0) {
		intf->out_error = ret;
	} else {
		intf->out_error = 0;
		intf->out_cons = cons + ret;
		prod = intf->out_prod;
	}
	/* update the indexes, then notify the other end */
	virt_wmb();
	if (prod != cons + ret)
		atomic_inc(&map->write);
	notify_remote_via_irq(map->irq);
}