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
struct timer_list {int dummy; } ;

/* Variables and functions */
 int ALI_7101_GPIO_O ; 
 int ALI_7101_WDT ; 
 char ALI_WDT_ARM ; 
 scalar_t__ WDT_INTERVAL ; 
 int /*<<< orphan*/  alim7101_pmu ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  next_heartbeat ; 
 int /*<<< orphan*/  pci_read_config_byte (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  pci_write_config_byte (int /*<<< orphan*/ ,int,char) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 scalar_t__ time_before (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 
 scalar_t__ use_gpio ; 

__attribute__((used)) static void wdt_timer_ping(struct timer_list *unused)
{
	/* If we got a heartbeat pulse within the WDT_US_INTERVAL
	 * we agree to ping the WDT
	 */
	char tmp;

	if (time_before(jiffies, next_heartbeat)) {
		/* Ping the WDT (this is actually a disarm/arm sequence) */
		pci_read_config_byte(alim7101_pmu, 0x92, &tmp);
		pci_write_config_byte(alim7101_pmu,
					ALI_7101_WDT, (tmp & ~ALI_WDT_ARM));
		pci_write_config_byte(alim7101_pmu,
					ALI_7101_WDT, (tmp | ALI_WDT_ARM));
		if (use_gpio) {
			pci_read_config_byte(alim7101_pmu,
					ALI_7101_GPIO_O, &tmp);
			pci_write_config_byte(alim7101_pmu,
					ALI_7101_GPIO_O, tmp | 0x20);
			pci_write_config_byte(alim7101_pmu,
					ALI_7101_GPIO_O, tmp & ~0x20);
		}
	} else {
		pr_warn("Heartbeat lost! Will not ping the watchdog\n");
	}
	/* Re-set the timer interval */
	mod_timer(&timer, jiffies + WDT_INTERVAL);
}