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
struct nvme_completion {scalar_t__ command_id; int /*<<< orphan*/  result; int /*<<< orphan*/  status; } ;
struct nvme_tcp_rsp_pdu {struct nvme_completion cqe; } ;
struct nvme_tcp_queue {TYPE_1__* ctrl; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 scalar_t__ NVME_AQ_BLK_MQ_DEPTH ; 
 int /*<<< orphan*/  nvme_complete_async_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nvme_tcp_process_nvme_cqe (struct nvme_tcp_queue*,struct nvme_completion*) ; 
 scalar_t__ nvme_tcp_queue_id (struct nvme_tcp_queue*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nvme_tcp_handle_comp(struct nvme_tcp_queue *queue,
		struct nvme_tcp_rsp_pdu *pdu)
{
	struct nvme_completion *cqe = &pdu->cqe;
	int ret = 0;

	/*
	 * AEN requests are special as they don't time out and can
	 * survive any kind of queue freeze and often don't respond to
	 * aborts.  We don't even bother to allocate a struct request
	 * for them but rather special case them here.
	 */
	if (unlikely(nvme_tcp_queue_id(queue) == 0 &&
	    cqe->command_id >= NVME_AQ_BLK_MQ_DEPTH))
		nvme_complete_async_event(&queue->ctrl->ctrl, cqe->status,
				&cqe->result);
	else
		ret = nvme_tcp_process_nvme_cqe(queue, cqe);

	return ret;
}