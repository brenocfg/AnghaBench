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
 int /*<<< orphan*/  intel_soc_dts_iosf_interrupt_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  soc_dts ; 

__attribute__((used)) static irqreturn_t soc_irq_thread_fn(int irq, void *dev_data)
{
	pr_debug("proc_thermal_interrupt\n");
	intel_soc_dts_iosf_interrupt_handler(soc_dts);

	return IRQ_HANDLED;
}