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
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ timer_started; int threshold; int /*<<< orphan*/  timer_control_addr; int /*<<< orphan*/  timer_load_count_addr; int /*<<< orphan*/  timer_interrupt_status_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 TYPE_1__ watchdog_device ; 

__attribute__((used)) static irqreturn_t watchdog_timer_interrupt(int irq, void *dev_id)
{
	int int_status;
	int_status = ioread32(watchdog_device.timer_interrupt_status_addr);

	pr_debug("irq, int_status: %x\n", int_status);

	if (int_status != 0)
		return IRQ_NONE;

	/* has the timer been started? If not, then this is spurious */
	if (watchdog_device.timer_started == 0) {
		pr_debug("spurious interrupt received\n");
		return IRQ_HANDLED;
	}

	/* temporarily disable the timer */
	iowrite32(0x00000002, watchdog_device.timer_control_addr);

	/* set the timer to the threshold */
	iowrite32(watchdog_device.threshold,
		  watchdog_device.timer_load_count_addr);

	/* allow the timer to run */
	iowrite32(0x00000003, watchdog_device.timer_control_addr);

	return IRQ_HANDLED;
}