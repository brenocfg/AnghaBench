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
struct xenvif_queue {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 long schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 
 scalar_t__ xenvif_have_rx_work (struct xenvif_queue*) ; 
 int /*<<< orphan*/  xenvif_rx_queue_timeout (struct xenvif_queue*) ; 

__attribute__((used)) static void xenvif_wait_for_rx_work(struct xenvif_queue *queue)
{
	DEFINE_WAIT(wait);

	if (xenvif_have_rx_work(queue))
		return;

	for (;;) {
		long ret;

		prepare_to_wait(&queue->wq, &wait, TASK_INTERRUPTIBLE);
		if (xenvif_have_rx_work(queue))
			break;
		ret = schedule_timeout(xenvif_rx_queue_timeout(queue));
		if (!ret)
			break;
	}
	finish_wait(&queue->wq, &wait);
}