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
struct vmci_queue {TYPE_1__* kernel_if; } ;
struct TYPE_2__ {int /*<<< orphan*/ * mutex; int /*<<< orphan*/  __mutex; scalar_t__ host; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qp_init_queue_mutex(struct vmci_queue *produce_q,
				struct vmci_queue *consume_q)
{
	/*
	 * Only the host queue has shared state - the guest queues do not
	 * need to synchronize access using a queue mutex.
	 */

	if (produce_q->kernel_if->host) {
		produce_q->kernel_if->mutex = &produce_q->kernel_if->__mutex;
		consume_q->kernel_if->mutex = &produce_q->kernel_if->__mutex;
		mutex_init(produce_q->kernel_if->mutex);
	}
}