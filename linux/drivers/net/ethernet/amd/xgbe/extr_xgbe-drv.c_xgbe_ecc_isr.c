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
struct xgbe_prv_data {int /*<<< orphan*/  tasklet_ecc; scalar_t__ isr_as_tasklet; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xgbe_ecc_isr_task (unsigned long) ; 

__attribute__((used)) static irqreturn_t xgbe_ecc_isr(int irq, void *data)
{
	struct xgbe_prv_data *pdata = data;

	if (pdata->isr_as_tasklet)
		tasklet_schedule(&pdata->tasklet_ecc);
	else
		xgbe_ecc_isr_task((unsigned long)pdata);

	return IRQ_HANDLED;
}