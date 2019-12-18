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
struct nvme_tcp_queue {int /*<<< orphan*/  flags; } ;
struct nvme_tcp_ctrl {struct nvme_tcp_queue* queues; } ;
struct nvme_ctrl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_TCP_Q_LIVE ; 
 int /*<<< orphan*/  __nvme_tcp_stop_queue (struct nvme_tcp_queue*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nvme_tcp_ctrl* to_tcp_ctrl (struct nvme_ctrl*) ; 

__attribute__((used)) static void nvme_tcp_stop_queue(struct nvme_ctrl *nctrl, int qid)
{
	struct nvme_tcp_ctrl *ctrl = to_tcp_ctrl(nctrl);
	struct nvme_tcp_queue *queue = &ctrl->queues[qid];

	if (!test_and_clear_bit(NVME_TCP_Q_LIVE, &queue->flags))
		return;

	__nvme_tcp_stop_queue(queue);
}