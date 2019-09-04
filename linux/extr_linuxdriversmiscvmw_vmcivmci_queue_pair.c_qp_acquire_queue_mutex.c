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
struct TYPE_2__ {int /*<<< orphan*/  mutex; scalar_t__ host; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qp_acquire_queue_mutex(struct vmci_queue *queue)
{
	if (queue->kernel_if->host)
		mutex_lock(queue->kernel_if->mutex);
}