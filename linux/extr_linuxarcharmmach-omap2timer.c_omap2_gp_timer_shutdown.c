#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct clock_event_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_TIMER_POSTED ; 
 int /*<<< orphan*/  __omap_dm_timer_stop (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ clkev ; 

__attribute__((used)) static int omap2_gp_timer_shutdown(struct clock_event_device *evt)
{
	__omap_dm_timer_stop(&clkev, OMAP_TIMER_POSTED, clkev.rate);
	return 0;
}