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
struct sock {int sk_state; int /*<<< orphan*/  sk_callback_lock; struct nvmet_tcp_queue* sk_user_data; } ;
struct nvmet_tcp_queue {int /*<<< orphan*/  idx; } ;

/* Variables and functions */
#define  TCP_CLOSE 130 
#define  TCP_CLOSE_WAIT 129 
#define  TCP_FIN_WAIT1 128 
 int /*<<< orphan*/  nvmet_tcp_schedule_release_queue (struct nvmet_tcp_queue*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvmet_tcp_state_change(struct sock *sk)
{
	struct nvmet_tcp_queue *queue;

	write_lock_bh(&sk->sk_callback_lock);
	queue = sk->sk_user_data;
	if (!queue)
		goto done;

	switch (sk->sk_state) {
	case TCP_FIN_WAIT1:
	case TCP_CLOSE_WAIT:
	case TCP_CLOSE:
		/* FALLTHRU */
		sk->sk_user_data = NULL;
		nvmet_tcp_schedule_release_queue(queue);
		break;
	default:
		pr_warn("queue %d unhandled state %d\n",
			queue->idx, sk->sk_state);
	}
done:
	write_unlock_bh(&sk->sk_callback_lock);
}