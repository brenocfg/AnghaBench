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
typedef  size_t u32 ;
struct hl_hw_queue {int /*<<< orphan*/  ci; } ;
struct hl_device {struct hl_hw_queue* kernel_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  hl_queue_inc_ptr (int /*<<< orphan*/ ) ; 

void hl_hw_queue_inc_ci_kernel(struct hl_device *hdev, u32 hw_queue_id)
{
	struct hl_hw_queue *q = &hdev->kernel_queues[hw_queue_id];

	q->ci = hl_queue_inc_ptr(q->ci);
}