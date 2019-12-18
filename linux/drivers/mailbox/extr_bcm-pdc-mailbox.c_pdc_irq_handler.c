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
typedef  scalar_t__ u32 ;
struct pdc_state {int /*<<< orphan*/  rx_tasklet; scalar_t__ pdc_reg_vbase; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ PDC_INTMASK_OFFSET ; 
 scalar_t__ PDC_INTSTATUS_OFFSET ; 
 struct pdc_state* dev_get_drvdata (struct device*) ; 
 scalar_t__ ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t pdc_irq_handler(int irq, void *data)
{
	struct device *dev = (struct device *)data;
	struct pdc_state *pdcs = dev_get_drvdata(dev);
	u32 intstatus = ioread32(pdcs->pdc_reg_vbase + PDC_INTSTATUS_OFFSET);

	if (unlikely(intstatus == 0))
		return IRQ_NONE;

	/* Disable interrupts until soft handler runs */
	iowrite32(0, pdcs->pdc_reg_vbase + PDC_INTMASK_OFFSET);

	/* Clear interrupt flags in device */
	iowrite32(intstatus, pdcs->pdc_reg_vbase + PDC_INTSTATUS_OFFSET);

	/* Wakeup IRQ thread */
	tasklet_schedule(&pdcs->rx_tasklet);
	return IRQ_HANDLED;
}