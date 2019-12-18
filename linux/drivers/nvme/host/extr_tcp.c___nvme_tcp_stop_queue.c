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
struct nvme_tcp_queue {int /*<<< orphan*/  io_work; int /*<<< orphan*/  sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kernel_sock_shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_tcp_restore_sock_calls (struct nvme_tcp_queue*) ; 

__attribute__((used)) static void __nvme_tcp_stop_queue(struct nvme_tcp_queue *queue)
{
	kernel_sock_shutdown(queue->sock, SHUT_RDWR);
	nvme_tcp_restore_sock_calls(queue);
	cancel_work_sync(&queue->io_work);
}