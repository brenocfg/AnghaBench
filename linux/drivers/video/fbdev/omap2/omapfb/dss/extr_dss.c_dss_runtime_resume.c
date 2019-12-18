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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dss_restore_context () ; 
 int dss_set_min_bus_tput (struct device*,int) ; 
 int /*<<< orphan*/  pinctrl_pm_select_default_state (struct device*) ; 

__attribute__((used)) static int dss_runtime_resume(struct device *dev)
{
	int r;

	pinctrl_pm_select_default_state(dev);

	/*
	 * Set an arbitrarily high tput request to ensure OPP100.
	 * What we should really do is to make a request to stay in OPP100,
	 * without any tput requirements, but that is not currently possible
	 * via the PM layer.
	 */

	r = dss_set_min_bus_tput(dev, 1000000000);
	if (r)
		return r;

	dss_restore_context();
	return 0;
}