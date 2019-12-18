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
 int /*<<< orphan*/  WDOG_CTRL_ACTION_FCR ; 
 int /*<<< orphan*/  WDOG_REG_CTRL ; 
 int /*<<< orphan*/  ath79_wdt_keepalive () ; 
 int /*<<< orphan*/  ath79_wdt_rr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath79_wdt_wr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline void ath79_wdt_enable(void)
{
	ath79_wdt_keepalive();

	/*
	 * Updating the TIMER register requires a few microseconds
	 * on the AR934x SoCs at least. Use a small delay to ensure
	 * that the TIMER register is updated within the hardware
	 * before enabling the watchdog.
	 */
	udelay(2);

	ath79_wdt_wr(WDOG_REG_CTRL, WDOG_CTRL_ACTION_FCR);
	/* flush write */
	ath79_wdt_rr(WDOG_REG_CTRL);
}