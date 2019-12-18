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
struct hl_device {int dummy; } ;
struct hl_cq {scalar_t__ kernel_address; int /*<<< orphan*/  free_slots_cnt; scalar_t__ pi; scalar_t__ ci; } ;

/* Variables and functions */
 int /*<<< orphan*/  HL_CQ_LENGTH ; 
 int /*<<< orphan*/  HL_CQ_SIZE_IN_BYTES ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hl_cq_reset(struct hl_device *hdev, struct hl_cq *q)
{
	q->ci = 0;
	q->pi = 0;

	atomic_set(&q->free_slots_cnt, HL_CQ_LENGTH);

	/*
	 * It's not enough to just reset the PI/CI because the H/W may have
	 * written valid completion entries before it was halted and therefore
	 * we need to clean the actual queues so we won't process old entries
	 * when the device is operational again
	 */

	memset((void *) (uintptr_t) q->kernel_address, 0, HL_CQ_SIZE_IN_BYTES);
}