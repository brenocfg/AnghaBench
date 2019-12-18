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
struct watchdog_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIMER_REG_TMR1CTL ; 
 int /*<<< orphan*/  TMR1CTL_ENABLE ; 
 int /*<<< orphan*/  mt7621_wdt_ping (struct watchdog_device*) ; 
 int /*<<< orphan*/  rt_wdt_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_wdt_w32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt7621_wdt_stop(struct watchdog_device *w)
{
	u32 t;

	mt7621_wdt_ping(w);

	t = rt_wdt_r32(TIMER_REG_TMR1CTL);
	t &= ~TMR1CTL_ENABLE;
	rt_wdt_w32(TIMER_REG_TMR1CTL, t);

	return 0;
}