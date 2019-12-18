#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hl_hw_queue {scalar_t__ queue_type; int ci; int int_queue_len; } ;
struct hl_device {TYPE_1__* asic_funcs; struct hl_hw_queue* kernel_queues; scalar_t__ disabled; } ;
struct hl_cs {scalar_t__* jobs_in_queue_cnt; TYPE_2__* ctx; } ;
struct TYPE_4__ {struct hl_device* hdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* hw_queues_unlock ) (struct hl_device*) ;int /*<<< orphan*/  (* hw_queues_lock ) (struct hl_device*) ;} ;

/* Variables and functions */
 int HL_MAX_QUEUES ; 
 scalar_t__ QUEUE_TYPE_INT ; 
 int /*<<< orphan*/  stub1 (struct hl_device*) ; 
 int /*<<< orphan*/  stub2 (struct hl_device*) ; 

void hl_int_hw_queue_update_ci(struct hl_cs *cs)
{
	struct hl_device *hdev = cs->ctx->hdev;
	struct hl_hw_queue *q;
	int i;

	hdev->asic_funcs->hw_queues_lock(hdev);

	if (hdev->disabled)
		goto out;

	q = &hdev->kernel_queues[0];
	for (i = 0 ; i < HL_MAX_QUEUES ; i++, q++) {
		if (q->queue_type == QUEUE_TYPE_INT) {
			q->ci += cs->jobs_in_queue_cnt[i];
			q->ci &= ((q->int_queue_len << 1) - 1);
		}
	}

out:
	hdev->asic_funcs->hw_queues_unlock(hdev);
}