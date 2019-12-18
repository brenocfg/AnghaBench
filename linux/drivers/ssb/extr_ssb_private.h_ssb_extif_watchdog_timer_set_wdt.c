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
typedef  int /*<<< orphan*/  u32 ;
struct bcm47xx_wdt {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 ssb_extif_watchdog_timer_set_wdt(struct bcm47xx_wdt *wdt,
						   u32 ticks)
{
	return 0;
}