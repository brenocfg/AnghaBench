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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int clkevt_periodic ; 
 int /*<<< orphan*/  nmdk_clkevt_reset () ; 

__attribute__((used)) static int nmdk_clkevt_set_periodic(struct clock_event_device *evt)
{
	clkevt_periodic = true;
	nmdk_clkevt_reset();
	return 0;
}