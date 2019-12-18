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
typedef  int u32 ;
struct saa7146_dev {scalar_t__ ext_priv; } ;
struct budget {int /*<<< orphan*/  vpe_tasklet; } ;

/* Variables and functions */
 int MASK_10 ; 
 int /*<<< orphan*/  dprintk (int,char*,struct saa7146_dev*,struct budget*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

void ttpci_budget_irq10_handler(struct saa7146_dev *dev, u32 * isr)
{
	struct budget *budget = (struct budget *) dev->ext_priv;

	dprintk(8, "dev: %p, budget: %p\n", dev, budget);

	if (*isr & MASK_10)
		tasklet_schedule(&budget->vpe_tasklet);
}