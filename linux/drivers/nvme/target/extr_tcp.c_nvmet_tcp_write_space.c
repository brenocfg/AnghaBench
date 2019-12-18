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
struct sock {int /*<<< orphan*/  sk_callback_lock; TYPE_1__* sk_socket; struct nvmet_tcp_queue* sk_user_data; } ;
struct nvmet_tcp_queue {scalar_t__ state; int /*<<< orphan*/  io_work; int /*<<< orphan*/  cpu; int /*<<< orphan*/  (* write_space ) (struct sock*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ NVMET_TCP_Q_CONNECTING ; 
 int /*<<< orphan*/  SOCK_NOSPACE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmet_tcp_wq ; 
 int /*<<< orphan*/  queue_work_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ sk_stream_is_writeable (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void nvmet_tcp_write_space(struct sock *sk)
{
	struct nvmet_tcp_queue *queue;

	read_lock_bh(&sk->sk_callback_lock);
	queue = sk->sk_user_data;
	if (unlikely(!queue))
		goto out;

	if (unlikely(queue->state == NVMET_TCP_Q_CONNECTING)) {
		queue->write_space(sk);
		goto out;
	}

	if (sk_stream_is_writeable(sk)) {
		clear_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
		queue_work_on(queue->cpu, nvmet_tcp_wq, &queue->io_work);
	}
out:
	read_unlock_bh(&sk->sk_callback_lock);
}