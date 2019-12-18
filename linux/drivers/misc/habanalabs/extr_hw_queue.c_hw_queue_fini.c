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
struct hl_hw_queue {scalar_t__ queue_type; int /*<<< orphan*/  bus_address; scalar_t__ kernel_address; int /*<<< orphan*/  shadow_queue; int /*<<< orphan*/  valid; } ;
struct hl_device {TYPE_1__* asic_funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* asic_dma_free_coherent ) (struct hl_device*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* cpu_accessible_dma_pool_free ) (struct hl_device*,int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HL_QUEUE_SIZE_IN_BYTES ; 
 scalar_t__ QUEUE_TYPE_CPU ; 
 scalar_t__ QUEUE_TYPE_INT ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct hl_device*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub2 (struct hl_device*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hw_queue_fini(struct hl_device *hdev, struct hl_hw_queue *q)
{
	if (!q->valid)
		return;

	/*
	 * If we arrived here, there are no jobs waiting on this queue
	 * so we can safely remove it.
	 * This is because this function can only called when:
	 * 1. Either a context is deleted, which only can occur if all its
	 *    jobs were finished
	 * 2. A context wasn't able to be created due to failure or timeout,
	 *    which means there are no jobs on the queue yet
	 *
	 * The only exception are the queues of the kernel context, but
	 * if they are being destroyed, it means that the entire module is
	 * being removed. If the module is removed, it means there is no open
	 * user context. It also means that if a job was submitted by
	 * the kernel driver (e.g. context creation), the job itself was
	 * released by the kernel driver when a timeout occurred on its
	 * Completion. Thus, we don't need to release it again.
	 */

	if (q->queue_type == QUEUE_TYPE_INT)
		return;

	kfree(q->shadow_queue);

	if (q->queue_type == QUEUE_TYPE_CPU)
		hdev->asic_funcs->cpu_accessible_dma_pool_free(hdev,
					HL_QUEUE_SIZE_IN_BYTES,
					(void *) (uintptr_t) q->kernel_address);
	else
		hdev->asic_funcs->asic_dma_free_coherent(hdev,
					HL_QUEUE_SIZE_IN_BYTES,
					(void *) (uintptr_t) q->kernel_address,
					q->bus_address);
}