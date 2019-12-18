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
struct socket {TYPE_1__* sk; } ;
struct nvme_tcp_queue {int /*<<< orphan*/  write_space; int /*<<< orphan*/  state_change; int /*<<< orphan*/  data_ready; struct socket* sock; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk_callback_lock; int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_state_change; int /*<<< orphan*/  sk_data_ready; int /*<<< orphan*/ * sk_user_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_tcp_restore_sock_calls(struct nvme_tcp_queue *queue)
{
	struct socket *sock = queue->sock;

	write_lock_bh(&sock->sk->sk_callback_lock);
	sock->sk->sk_user_data  = NULL;
	sock->sk->sk_data_ready = queue->data_ready;
	sock->sk->sk_state_change = queue->state_change;
	sock->sk->sk_write_space  = queue->write_space;
	write_unlock_bh(&sock->sk->sk_callback_lock);
}