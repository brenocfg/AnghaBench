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
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct hl_hw_queue {scalar_t__ queue_type; } ;
struct hl_device {TYPE_1__* asic_funcs; scalar_t__ disabled; struct hl_hw_queue* kernel_queues; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* hw_queues_unlock ) (struct hl_device*) ;int /*<<< orphan*/  (* hw_queues_lock ) (struct hl_device*) ;} ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ QUEUE_TYPE_CPU ; 
 int ext_queue_sanity_checks (struct hl_device*,struct hl_hw_queue*,int,int) ; 
 int /*<<< orphan*/  ext_queue_submit_bd (struct hl_device*,struct hl_hw_queue*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct hl_device*) ; 
 int /*<<< orphan*/  stub2 (struct hl_device*) ; 

int hl_hw_queue_send_cb_no_cmpl(struct hl_device *hdev, u32 hw_queue_id,
				u32 cb_size, u64 cb_ptr)
{
	struct hl_hw_queue *q = &hdev->kernel_queues[hw_queue_id];
	int rc;

	/*
	 * The CPU queue is a synchronous queue with an effective depth of
	 * a single entry (although it is allocated with room for multiple
	 * entries). Therefore, there is a different lock, called
	 * send_cpu_message_lock, that serializes accesses to the CPU queue.
	 * As a result, we don't need to lock the access to the entire H/W
	 * queues module when submitting a JOB to the CPU queue
	 */
	if (q->queue_type != QUEUE_TYPE_CPU)
		hdev->asic_funcs->hw_queues_lock(hdev);

	if (hdev->disabled) {
		rc = -EPERM;
		goto out;
	}

	rc = ext_queue_sanity_checks(hdev, q, 1, false);
	if (rc)
		goto out;

	ext_queue_submit_bd(hdev, q, 0, cb_size, cb_ptr);

out:
	if (q->queue_type != QUEUE_TYPE_CPU)
		hdev->asic_funcs->hw_queues_unlock(hdev);

	return rc;
}