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
struct nvme_tcp_queue {int /*<<< orphan*/  pdu; int /*<<< orphan*/  sock; scalar_t__ data_digest; scalar_t__ hdr_digest; int /*<<< orphan*/  flags; } ;
struct nvme_tcp_ctrl {struct nvme_tcp_queue* queues; } ;
struct nvme_ctrl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_TCP_Q_ALLOCATED ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_tcp_free_crypto (struct nvme_tcp_queue*) ; 
 int /*<<< orphan*/  sock_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nvme_tcp_ctrl* to_tcp_ctrl (struct nvme_ctrl*) ; 

__attribute__((used)) static void nvme_tcp_free_queue(struct nvme_ctrl *nctrl, int qid)
{
	struct nvme_tcp_ctrl *ctrl = to_tcp_ctrl(nctrl);
	struct nvme_tcp_queue *queue = &ctrl->queues[qid];

	if (!test_and_clear_bit(NVME_TCP_Q_ALLOCATED, &queue->flags))
		return;

	if (queue->hdr_digest || queue->data_digest)
		nvme_tcp_free_crypto(queue);

	sock_release(queue->sock);
	kfree(queue->pdu);
}