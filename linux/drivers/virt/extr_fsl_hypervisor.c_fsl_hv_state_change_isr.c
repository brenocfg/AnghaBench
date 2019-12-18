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
struct doorbell_isr {int /*<<< orphan*/  partition; int /*<<< orphan*/  doorbell; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int FH_PARTITION_STOPPED ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int fh_partition_get_status (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  fsl_hv_queue_doorbell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t fsl_hv_state_change_isr(int irq, void *data)
{
	unsigned int status;
	struct doorbell_isr *dbisr = data;
	int ret;

	/* It's still a doorbell, so add it to all the queues. */
	fsl_hv_queue_doorbell(dbisr->doorbell);

	/* Determine the new state, and if it's stopped, notify the clients. */
	ret = fh_partition_get_status(dbisr->partition, &status);
	if (!ret && (status == FH_PARTITION_STOPPED))
		return IRQ_WAKE_THREAD;

	return IRQ_HANDLED;
}