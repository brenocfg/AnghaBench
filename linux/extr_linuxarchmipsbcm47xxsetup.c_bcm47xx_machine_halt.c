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

/* Variables and functions */
 int bcm47xx_bus_type ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  local_irq_disable () ; 

__attribute__((used)) static void bcm47xx_machine_halt(void)
{
	/* Disable interrupts and watchdog and spin forever */
	local_irq_disable();
	switch (bcm47xx_bus_type) {
#ifdef CONFIG_BCM47XX_SSB
	case BCM47XX_BUS_TYPE_SSB:
		ssb_watchdog_timer_set(&bcm47xx_bus.ssb, 0);
		break;
#endif
#ifdef CONFIG_BCM47XX_BCMA
	case BCM47XX_BUS_TYPE_BCMA:
		bcma_chipco_watchdog_timer_set(&bcm47xx_bus.bcma.bus.drv_cc, 0);
		break;
#endif
	}
	while (1)
		cpu_relax();
}