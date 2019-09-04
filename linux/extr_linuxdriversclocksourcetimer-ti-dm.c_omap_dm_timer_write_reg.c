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
struct omap_dm_timer {int /*<<< orphan*/  posted; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int _OMAP_TIMER_WAKEUP_EN_OFFSET ; 
 int /*<<< orphan*/  __omap_dm_timer_write (struct omap_dm_timer*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap_dm_timer_write_reg(struct omap_dm_timer *timer, u32 reg,
						u32 value)
{
	WARN_ON((reg & 0xff) < _OMAP_TIMER_WAKEUP_EN_OFFSET);
	__omap_dm_timer_write(timer, reg, value, timer->posted);
}