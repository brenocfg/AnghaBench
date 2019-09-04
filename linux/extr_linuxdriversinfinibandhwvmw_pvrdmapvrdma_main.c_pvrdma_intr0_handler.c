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
typedef  scalar_t__ u32 ;
struct pvrdma_dev {int /*<<< orphan*/  cmd_done; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  msix_enabled; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ PVRDMA_INTR_CAUSE_RESPONSE ; 
 int /*<<< orphan*/  PVRDMA_REG_ICR ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ pvrdma_read_reg (struct pvrdma_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t pvrdma_intr0_handler(int irq, void *dev_id)
{
	u32 icr = PVRDMA_INTR_CAUSE_RESPONSE;
	struct pvrdma_dev *dev = dev_id;

	dev_dbg(&dev->pdev->dev, "interrupt 0 (response) handler\n");

	if (!dev->pdev->msix_enabled) {
		/* Legacy intr */
		icr = pvrdma_read_reg(dev, PVRDMA_REG_ICR);
		if (icr == 0)
			return IRQ_NONE;
	}

	if (icr == PVRDMA_INTR_CAUSE_RESPONSE)
		complete(&dev->cmd_done);

	return IRQ_HANDLED;
}