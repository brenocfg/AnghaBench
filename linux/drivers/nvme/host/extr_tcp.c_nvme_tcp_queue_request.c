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
struct nvme_tcp_request {int /*<<< orphan*/  entry; struct nvme_tcp_queue* queue; } ;
struct nvme_tcp_queue {int /*<<< orphan*/  io_work; int /*<<< orphan*/  io_cpu; int /*<<< orphan*/  lock; int /*<<< orphan*/  send_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_tcp_wq ; 
 int /*<<< orphan*/  queue_work_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void nvme_tcp_queue_request(struct nvme_tcp_request *req)
{
	struct nvme_tcp_queue *queue = req->queue;

	spin_lock(&queue->lock);
	list_add_tail(&req->entry, &queue->send_list);
	spin_unlock(&queue->lock);

	queue_work_on(queue->io_cpu, nvme_tcp_wq, &queue->io_work);
}