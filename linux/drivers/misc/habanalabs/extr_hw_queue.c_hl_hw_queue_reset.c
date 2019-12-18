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
struct hl_hw_queue {scalar_t__ queue_type; scalar_t__ ci; scalar_t__ pi; int /*<<< orphan*/  valid; } ;
struct hl_device {struct hl_hw_queue* kernel_queues; } ;

/* Variables and functions */
 int HL_MAX_QUEUES ; 
 scalar_t__ QUEUE_TYPE_CPU ; 

void hl_hw_queue_reset(struct hl_device *hdev, bool hard_reset)
{
	struct hl_hw_queue *q;
	int i;

	for (i = 0, q = hdev->kernel_queues ; i < HL_MAX_QUEUES ; i++, q++) {
		if ((!q->valid) ||
			((!hard_reset) && (q->queue_type == QUEUE_TYPE_CPU)))
			continue;
		q->pi = q->ci = 0;
	}
}