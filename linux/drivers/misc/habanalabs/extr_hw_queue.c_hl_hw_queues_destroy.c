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
struct hl_hw_queue {int dummy; } ;
struct hl_device {struct hl_hw_queue* kernel_queues; } ;

/* Variables and functions */
 int HL_MAX_QUEUES ; 
 int /*<<< orphan*/  hw_queue_fini (struct hl_device*,struct hl_hw_queue*) ; 
 int /*<<< orphan*/  kfree (struct hl_hw_queue*) ; 

void hl_hw_queues_destroy(struct hl_device *hdev)
{
	struct hl_hw_queue *q;
	int i;

	for (i = 0, q = hdev->kernel_queues ; i < HL_MAX_QUEUES ; i++, q++)
		hw_queue_fini(hdev, q);

	kfree(hdev->kernel_queues);
}