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
typedef  scalar_t__ u8 ;
struct nvme_tcp_request {struct nvme_tcp_queue* queue; int /*<<< orphan*/  pdu; } ;
struct nvme_tcp_queue {int /*<<< orphan*/  pf_cache; } ;
struct nvme_tcp_ctrl {struct nvme_tcp_queue* queues; struct nvme_tcp_request async_req; } ;
struct nvme_tcp_cmd_pdu {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int __GFP_ZERO ; 
 scalar_t__ nvme_tcp_hdgst_len (struct nvme_tcp_queue*) ; 
 int /*<<< orphan*/  page_frag_alloc (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static int nvme_tcp_alloc_async_req(struct nvme_tcp_ctrl *ctrl)
{
	struct nvme_tcp_queue *queue = &ctrl->queues[0];
	struct nvme_tcp_request *async = &ctrl->async_req;
	u8 hdgst = nvme_tcp_hdgst_len(queue);

	async->pdu = page_frag_alloc(&queue->pf_cache,
		sizeof(struct nvme_tcp_cmd_pdu) + hdgst,
		GFP_KERNEL | __GFP_ZERO);
	if (!async->pdu)
		return -ENOMEM;

	async->queue = &ctrl->queues[0];
	return 0;
}