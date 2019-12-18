#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket {TYPE_1__* sk; } ;
struct msghdr {int /*<<< orphan*/  msg_iter; int /*<<< orphan*/  msg_flags; } ;
struct kvec {void* iov_base; int iov_len; } ;
struct TYPE_4__ {int /*<<< orphan*/  comm; } ;
struct TYPE_3__ {int /*<<< orphan*/  sk_allocation; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 int /*<<< orphan*/  MSG_WAITALL ; 
 int /*<<< orphan*/  READ ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  iov_iter_kvec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kvec*,int,int) ; 
 scalar_t__ msg_data_left (struct msghdr*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int sock_recvmsg (struct socket*,struct msghdr*,int /*<<< orphan*/ ) ; 
 scalar_t__ usbip_dbg_flag_xmit ; 
 int /*<<< orphan*/  usbip_dbg_xmit (char*) ; 
 int /*<<< orphan*/  usbip_dump_buffer (void*,int) ; 

int usbip_recv(struct socket *sock, void *buf, int size)
{
	int result;
	struct kvec iov = {.iov_base = buf, .iov_len = size};
	struct msghdr msg = {.msg_flags = MSG_NOSIGNAL};
	int total = 0;

	if (!sock || !buf || !size)
		return -EINVAL;

	iov_iter_kvec(&msg.msg_iter, READ, &iov, 1, size);

	usbip_dbg_xmit("enter\n");

	do {
		sock->sk->sk_allocation = GFP_NOIO;

		result = sock_recvmsg(sock, &msg, MSG_WAITALL);
		if (result <= 0)
			goto err;

		total += result;
	} while (msg_data_left(&msg));

	if (usbip_dbg_flag_xmit) {
		if (!in_interrupt())
			pr_debug("%-10s:", current->comm);
		else
			pr_debug("interrupt  :");

		pr_debug("receiving....\n");
		usbip_dump_buffer(buf, size);
		pr_debug("received, osize %d ret %d size %zd total %d\n",
			 size, result, msg_data_left(&msg), total);
	}

	return total;

err:
	return result;
}