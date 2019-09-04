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
struct i40iw_ceq {int irq; int /*<<< orphan*/  dpc_tasklet; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  i40iw_pr_err (char*,int,int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t i40iw_ceq_handler(int irq, void *data)
{
	struct i40iw_ceq *iwceq = (struct i40iw_ceq *)data;

	if (iwceq->irq != irq)
		i40iw_pr_err("expected irq = %d received irq = %d\n", iwceq->irq, irq);
	tasklet_schedule(&iwceq->dpc_tasklet);
	return IRQ_HANDLED;
}