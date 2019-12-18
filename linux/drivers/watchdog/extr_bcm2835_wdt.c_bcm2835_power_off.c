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
struct bcm2835_wdt {scalar_t__ base; } ;

/* Variables and functions */
 int PM_PASSWORD ; 
 scalar_t__ PM_RSTS ; 
 int PM_RSTS_RASPBERRYPI_HALT ; 
 int /*<<< orphan*/  __bcm2835_restart (struct bcm2835_wdt*) ; 
 struct bcm2835_wdt* bcm2835_power_off_wdt ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void bcm2835_power_off(void)
{
	struct bcm2835_wdt *wdt = bcm2835_power_off_wdt;
	u32 val;

	/*
	 * We set the watchdog hard reset bit here to distinguish this reset
	 * from the normal (full) reset. bootcode.bin will not reboot after a
	 * hard reset.
	 */
	val = readl_relaxed(wdt->base + PM_RSTS);
	val |= PM_PASSWORD | PM_RSTS_RASPBERRYPI_HALT;
	writel_relaxed(val, wdt->base + PM_RSTS);

	/* Continue with normal reset mechanism */
	__bcm2835_restart(wdt);
}