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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ OMAP1_MPUIO_BASE ; 
 scalar_t__ OMAP_MPUIO_KBD_MASKIT ; 
 int /*<<< orphan*/  kp_tasklet ; 
 int /*<<< orphan*/  omap_writew (int,scalar_t__) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t omap_kp_interrupt(int irq, void *dev_id)
{
	/* disable keyboard interrupt and schedule for handling */
	omap_writew(1, OMAP1_MPUIO_BASE + OMAP_MPUIO_KBD_MASKIT);

	tasklet_schedule(&kp_tasklet);

	return IRQ_HANDLED;
}