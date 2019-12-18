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
struct nvme_tcp_rsp_pdu {int dummy; } ;
struct nvme_tcp_queue {int data_remaining; scalar_t__ ddgst_remaining; scalar_t__ pdu_offset; scalar_t__ pdu_remaining; } ;

/* Variables and functions */
 scalar_t__ nvme_tcp_hdgst_len (struct nvme_tcp_queue*) ; 

__attribute__((used)) static void nvme_tcp_init_recv_ctx(struct nvme_tcp_queue *queue)
{
	queue->pdu_remaining = sizeof(struct nvme_tcp_rsp_pdu) +
				nvme_tcp_hdgst_len(queue);
	queue->pdu_offset = 0;
	queue->data_remaining = -1;
	queue->ddgst_remaining = 0;
}