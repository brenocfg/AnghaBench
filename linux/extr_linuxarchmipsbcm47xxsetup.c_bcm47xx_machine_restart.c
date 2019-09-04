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
 int /*<<< orphan*/  pr_alert (char*) ; 

__attribute__((used)) static void bcm47xx_machine_restart(char *command)
{
	pr_alert("Please stand by while rebooting the system...\n");
	local_irq_disable();
	/* Set the watchdog timer to reset immediately */
	switch (bcm47xx_bus_type) {
#ifdef CONFIG_BCM47XX_SSB
	case BCM47XX_BUS_TYPE_SSB:
		if (bcm47xx_bus.ssb.chip_id == 0x4785)
			write_c0_diag4(1 << 22);
		ssb_watchdog_timer_set(&bcm47xx_bus.ssb, 1);
		if (bcm47xx_bus.ssb.chip_id == 0x4785) {
			__asm__ __volatile__(
				".set\tmips3\n\t"
				"sync\n\t"
				"wait\n\t"
				".set\tmips0");
		}
		break;
#endif
#ifdef CONFIG_BCM47XX_BCMA
	case BCM47XX_BUS_TYPE_BCMA:
		bcma_chipco_watchdog_timer_set(&bcm47xx_bus.bcma.bus.drv_cc, 1);
		break;
#endif
	}
	while (1)
		cpu_relax();
}