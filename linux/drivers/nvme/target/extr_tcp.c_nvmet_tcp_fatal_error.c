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
struct TYPE_2__ {scalar_t__ ctrl; } ;
struct nvmet_tcp_queue {int /*<<< orphan*/  sock; TYPE_1__ nvme_sq; int /*<<< orphan*/  rcv_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVMET_TCP_RECV_ERR ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  kernel_sock_shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_ctrl_fatal_error (scalar_t__) ; 

__attribute__((used)) static void nvmet_tcp_fatal_error(struct nvmet_tcp_queue *queue)
{
	queue->rcv_state = NVMET_TCP_RECV_ERR;
	if (queue->nvme_sq.ctrl)
		nvmet_ctrl_fatal_error(queue->nvme_sq.ctrl);
	else
		kernel_sock_shutdown(queue->sock, SHUT_RDWR);
}