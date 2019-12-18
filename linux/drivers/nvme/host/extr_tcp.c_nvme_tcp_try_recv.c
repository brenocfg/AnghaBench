#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct socket {TYPE_2__* ops; struct sock* sk; } ;
struct sock {int dummy; } ;
struct nvme_tcp_queue {scalar_t__ nr_cqe; struct socket* sock; } ;
struct TYPE_5__ {struct nvme_tcp_queue* data; } ;
struct TYPE_7__ {int count; TYPE_1__ arg; } ;
typedef  TYPE_3__ read_descriptor_t ;
struct TYPE_6__ {int (* read_sock ) (struct sock*,TYPE_3__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  nvme_tcp_recv_skb ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int stub1 (struct sock*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvme_tcp_try_recv(struct nvme_tcp_queue *queue)
{
	struct socket *sock = queue->sock;
	struct sock *sk = sock->sk;
	read_descriptor_t rd_desc;
	int consumed;

	rd_desc.arg.data = queue;
	rd_desc.count = 1;
	lock_sock(sk);
	queue->nr_cqe = 0;
	consumed = sock->ops->read_sock(sk, &rd_desc, nvme_tcp_recv_skb);
	release_sock(sk);
	return consumed;
}