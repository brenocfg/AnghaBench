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
struct nvmet_tcp_queue {scalar_t__ state; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  release_work; } ;

/* Variables and functions */
 scalar_t__ NVMET_TCP_Q_DISCONNECTING ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvmet_tcp_schedule_release_queue(struct nvmet_tcp_queue *queue)
{
	spin_lock(&queue->state_lock);
	if (queue->state != NVMET_TCP_Q_DISCONNECTING) {
		queue->state = NVMET_TCP_Q_DISCONNECTING;
		schedule_work(&queue->release_work);
	}
	spin_unlock(&queue->state_lock);
}