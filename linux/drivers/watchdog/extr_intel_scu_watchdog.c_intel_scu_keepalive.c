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
struct TYPE_2__ {int soft_threshold; int /*<<< orphan*/  timer_control_addr; int /*<<< orphan*/  timer_load_count_addr; int /*<<< orphan*/  timer_clear_interrupt_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ ) ; 
 TYPE_1__ watchdog_device ; 

__attribute__((used)) static int intel_scu_keepalive(void)
{

	/* read eoi register - clears interrupt */
	ioread32(watchdog_device.timer_clear_interrupt_addr);

	/* temporarily disable the timer */
	iowrite32(0x00000002, watchdog_device.timer_control_addr);

	/* set the timer to the soft_threshold */
	iowrite32(watchdog_device.soft_threshold,
		  watchdog_device.timer_load_count_addr);

	/* allow the timer to run */
	iowrite32(0x00000003, watchdog_device.timer_control_addr);

	return 0;
}