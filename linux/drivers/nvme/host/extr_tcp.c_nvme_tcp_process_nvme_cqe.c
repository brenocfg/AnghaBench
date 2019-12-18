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
struct request {int dummy; } ;
struct nvme_tcp_queue {int /*<<< orphan*/  nr_cqe; TYPE_1__* ctrl; } ;
struct nvme_completion {int /*<<< orphan*/  result; int /*<<< orphan*/  status; int /*<<< orphan*/  command_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct TYPE_3__ {TYPE_2__ ctrl; } ;

/* Variables and functions */
 int EINVAL ; 
 struct request* blk_mq_tag_to_rq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_end_request (struct request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_tcp_error_recovery (TYPE_2__*) ; 
 int /*<<< orphan*/  nvme_tcp_queue_id (struct nvme_tcp_queue*) ; 
 int /*<<< orphan*/  nvme_tcp_tagset (struct nvme_tcp_queue*) ; 

__attribute__((used)) static int nvme_tcp_process_nvme_cqe(struct nvme_tcp_queue *queue,
		struct nvme_completion *cqe)
{
	struct request *rq;

	rq = blk_mq_tag_to_rq(nvme_tcp_tagset(queue), cqe->command_id);
	if (!rq) {
		dev_err(queue->ctrl->ctrl.device,
			"queue %d tag 0x%x not found\n",
			nvme_tcp_queue_id(queue), cqe->command_id);
		nvme_tcp_error_recovery(&queue->ctrl->ctrl);
		return -EINVAL;
	}

	nvme_end_request(rq, cqe->status, cqe->result);
	queue->nr_cqe++;

	return 0;
}