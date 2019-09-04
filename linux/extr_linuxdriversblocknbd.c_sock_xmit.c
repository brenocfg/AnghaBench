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
struct socket {TYPE_2__* sk; } ;
struct nbd_device {int /*<<< orphan*/  disk; struct nbd_config* config; } ;
struct nbd_config {TYPE_1__** socks; } ;
struct iov_iter {int dummy; } ;
struct msghdr {int msg_flags; scalar_t__ msg_controllen; int /*<<< orphan*/ * msg_control; scalar_t__ msg_namelen; int /*<<< orphan*/ * msg_name; struct iov_iter msg_iter; } ;
struct TYPE_4__ {int sk_allocation; } ;
struct TYPE_3__ {struct socket* sock; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPIPE ; 
 int GFP_NOIO ; 
 int MSG_NOSIGNAL ; 
 int __GFP_MEMALLOC ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  disk_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memalloc_noreclaim_restore (unsigned int) ; 
 unsigned int memalloc_noreclaim_save () ; 
 scalar_t__ msg_data_left (struct msghdr*) ; 
 int sock_recvmsg (struct socket*,struct msghdr*,int) ; 
 int sock_sendmsg (struct socket*,struct msghdr*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int sock_xmit(struct nbd_device *nbd, int index, int send,
		     struct iov_iter *iter, int msg_flags, int *sent)
{
	struct nbd_config *config = nbd->config;
	struct socket *sock = config->socks[index]->sock;
	int result;
	struct msghdr msg;
	unsigned int noreclaim_flag;

	if (unlikely(!sock)) {
		dev_err_ratelimited(disk_to_dev(nbd->disk),
			"Attempted %s on closed socket in sock_xmit\n",
			(send ? "send" : "recv"));
		return -EINVAL;
	}

	msg.msg_iter = *iter;

	noreclaim_flag = memalloc_noreclaim_save();
	do {
		sock->sk->sk_allocation = GFP_NOIO | __GFP_MEMALLOC;
		msg.msg_name = NULL;
		msg.msg_namelen = 0;
		msg.msg_control = NULL;
		msg.msg_controllen = 0;
		msg.msg_flags = msg_flags | MSG_NOSIGNAL;

		if (send)
			result = sock_sendmsg(sock, &msg);
		else
			result = sock_recvmsg(sock, &msg, msg.msg_flags);

		if (result <= 0) {
			if (result == 0)
				result = -EPIPE; /* short read */
			break;
		}
		if (sent)
			*sent += result;
	} while (msg_data_left(&msg));

	memalloc_noreclaim_restore(noreclaim_flag);

	return result;
}