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
struct mmp_tdma_chan {int /*<<< orphan*/  tasklet; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ mmp_tdma_clear_chan_irq (struct mmp_tdma_chan*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mmp_tdma_chan_handler(int irq, void *dev_id)
{
	struct mmp_tdma_chan *tdmac = dev_id;

	if (mmp_tdma_clear_chan_irq(tdmac) == 0) {
		tasklet_schedule(&tdmac->tasklet);
		return IRQ_HANDLED;
	} else
		return IRQ_NONE;
}