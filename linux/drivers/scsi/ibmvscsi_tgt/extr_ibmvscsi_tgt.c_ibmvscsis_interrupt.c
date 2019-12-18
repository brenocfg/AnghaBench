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
struct scsi_info {int /*<<< orphan*/  work_task; int /*<<< orphan*/  dma_dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vio_disable_interrupts (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ibmvscsis_interrupt(int dummy, void *data)
{
	struct scsi_info *vscsi = data;

	vio_disable_interrupts(vscsi->dma_dev);
	tasklet_schedule(&vscsi->work_task);

	return IRQ_HANDLED;
}