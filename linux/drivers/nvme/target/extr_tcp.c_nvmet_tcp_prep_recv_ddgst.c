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
struct nvmet_tcp_queue {int /*<<< orphan*/  rcv_state; int /*<<< orphan*/  left; scalar_t__ offset; int /*<<< orphan*/  rcv_hash; } ;
struct nvmet_tcp_cmd {struct nvmet_tcp_queue* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVMET_TCP_RECV_DDGST ; 
 int /*<<< orphan*/  NVME_TCP_DIGEST_LENGTH ; 
 int /*<<< orphan*/  nvmet_tcp_ddgst (int /*<<< orphan*/ ,struct nvmet_tcp_cmd*) ; 

__attribute__((used)) static void nvmet_tcp_prep_recv_ddgst(struct nvmet_tcp_cmd *cmd)
{
	struct nvmet_tcp_queue *queue = cmd->queue;

	nvmet_tcp_ddgst(queue->rcv_hash, cmd);
	queue->offset = 0;
	queue->left = NVME_TCP_DIGEST_LENGTH;
	queue->rcv_state = NVMET_TCP_RECV_DDGST;
}