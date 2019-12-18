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
struct sock {int sk_state; int /*<<< orphan*/  sk_callback_lock; struct nvme_tcp_queue* sk_user_data; } ;
struct nvme_tcp_queue {int /*<<< orphan*/  (* state_change ) (struct sock*) ;TYPE_1__* ctrl; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct TYPE_3__ {TYPE_2__ ctrl; } ;

/* Variables and functions */
#define  TCP_CLOSE 132 
#define  TCP_CLOSE_WAIT 131 
#define  TCP_FIN_WAIT1 130 
#define  TCP_FIN_WAIT2 129 
#define  TCP_LAST_ACK 128 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvme_tcp_error_recovery (TYPE_2__*) ; 
 int /*<<< orphan*/  nvme_tcp_queue_id (struct nvme_tcp_queue*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void nvme_tcp_state_change(struct sock *sk)
{
	struct nvme_tcp_queue *queue;

	read_lock(&sk->sk_callback_lock);
	queue = sk->sk_user_data;
	if (!queue)
		goto done;

	switch (sk->sk_state) {
	case TCP_CLOSE:
	case TCP_CLOSE_WAIT:
	case TCP_LAST_ACK:
	case TCP_FIN_WAIT1:
	case TCP_FIN_WAIT2:
		/* fallthrough */
		nvme_tcp_error_recovery(&queue->ctrl->ctrl);
		break;
	default:
		dev_info(queue->ctrl->ctrl.device,
			"queue %d socket state %d\n",
			nvme_tcp_queue_id(queue), sk->sk_state);
	}

	queue->state_change(sk);
done:
	read_unlock(&sk->sk_callback_lock);
}