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
 unsigned long HV_EOK ; 
 unsigned long HV_EWOULDBLOCK ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 unsigned long sun4v_tod_get (unsigned long*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static unsigned long hypervisor_get_time(void)
{
	unsigned long ret, time;
	int retries = 10000;

retry:
	ret = sun4v_tod_get(&time);
	if (ret == HV_EOK)
		return time;
	if (ret == HV_EWOULDBLOCK) {
		if (--retries > 0) {
			udelay(100);
			goto retry;
		}
		pr_warn("tod_get() timed out.\n");
		return 0;
	}
	pr_warn("tod_get() not supported.\n");
	return 0;
}