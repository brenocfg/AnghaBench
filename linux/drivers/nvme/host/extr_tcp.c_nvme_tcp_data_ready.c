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
struct sock {int /*<<< orphan*/  sk_callback_lock; struct nvme_tcp_queue* sk_user_data; } ;
struct nvme_tcp_queue {int /*<<< orphan*/  io_work; int /*<<< orphan*/  io_cpu; scalar_t__ rd_enabled; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  nvme_tcp_wq ; 
 int /*<<< orphan*/  queue_work_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_tcp_data_ready(struct sock *sk)
{
	struct nvme_tcp_queue *queue;

	read_lock(&sk->sk_callback_lock);
	queue = sk->sk_user_data;
	if (likely(queue && queue->rd_enabled))
		queue_work_on(queue->io_cpu, nvme_tcp_wq, &queue->io_work);
	read_unlock(&sk->sk_callback_lock);
}