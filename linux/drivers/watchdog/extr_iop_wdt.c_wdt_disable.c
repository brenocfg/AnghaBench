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
 int /*<<< orphan*/  IOP_WDTCR_DIS ; 
 int /*<<< orphan*/  IOP_WDTCR_DIS_ARM ; 
 int /*<<< orphan*/  WDT_ENABLED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_lock ; 
 int /*<<< orphan*/  wdt_status ; 
 scalar_t__ wdt_supports_disable () ; 
 int /*<<< orphan*/  write_wdtcr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wdt_disable(void)
{
	/* Stop Counting */
	if (wdt_supports_disable()) {
		spin_lock(&wdt_lock);
		write_wdtcr(IOP_WDTCR_DIS_ARM);
		write_wdtcr(IOP_WDTCR_DIS);
		clear_bit(WDT_ENABLED, &wdt_status);
		spin_unlock(&wdt_lock);
		pr_info("Disabled\n");
		return 0;
	} else
		return 1;
}