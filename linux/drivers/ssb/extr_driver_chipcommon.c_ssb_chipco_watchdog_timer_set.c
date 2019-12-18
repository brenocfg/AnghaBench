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
struct ssb_chipcommon {int capabilities; } ;
typedef  enum ssb_clkmode { ____Placeholder_ssb_clkmode } ssb_clkmode ;

/* Variables and functions */
 int SSB_CHIPCO_CAP_PMU ; 
 int /*<<< orphan*/  SSB_CHIPCO_PMU_WATCHDOG ; 
 int /*<<< orphan*/  SSB_CHIPCO_WATCHDOG ; 
 int SSB_CLKMODE_DYNAMIC ; 
 int SSB_CLKMODE_FAST ; 
 int /*<<< orphan*/  chipco_write32 (struct ssb_chipcommon*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ssb_chipco_set_clockmode (struct ssb_chipcommon*,int) ; 
 int ssb_chipco_watchdog_get_max_timer (struct ssb_chipcommon*) ; 

u32 ssb_chipco_watchdog_timer_set(struct ssb_chipcommon *cc, u32 ticks)
{
	u32 maxt;
	enum ssb_clkmode clkmode;

	maxt = ssb_chipco_watchdog_get_max_timer(cc);
	if (cc->capabilities & SSB_CHIPCO_CAP_PMU) {
		if (ticks == 1)
			ticks = 2;
		else if (ticks > maxt)
			ticks = maxt;
		chipco_write32(cc, SSB_CHIPCO_PMU_WATCHDOG, ticks);
	} else {
		clkmode = ticks ? SSB_CLKMODE_FAST : SSB_CLKMODE_DYNAMIC;
		ssb_chipco_set_clockmode(cc, clkmode);
		if (ticks > maxt)
			ticks = maxt;
		/* instant NMI */
		chipco_write32(cc, SSB_CHIPCO_WATCHDOG, ticks);
	}
	return ticks;
}