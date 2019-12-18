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
struct nvmet_tcp_queue {int left; int /*<<< orphan*/  rcv_state; int /*<<< orphan*/ * cmd; scalar_t__ offset; } ;
struct nvme_tcp_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVMET_TCP_RECV_PDU ; 

__attribute__((used)) static void nvmet_prepare_receive_pdu(struct nvmet_tcp_queue *queue)
{
	queue->offset = 0;
	queue->left = sizeof(struct nvme_tcp_hdr);
	queue->cmd = NULL;
	queue->rcv_state = NVMET_TCP_RECV_PDU;
}