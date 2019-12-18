#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct watchdog_device {unsigned int timeout; TYPE_1__* info; scalar_t__ parent; } ;
struct device {scalar_t__ of_node; } ;
struct TYPE_2__ {scalar_t__ identity; } ;

/* Variables and functions */
 int EINVAL ; 
 char const* dev_name (scalar_t__) ; 
 scalar_t__ of_property_read_u32 (scalar_t__,char*,unsigned int*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  pr_warn (char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  watchdog_check_min_max_timeout (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_timeout_invalid (struct watchdog_device*,unsigned int) ; 

int watchdog_init_timeout(struct watchdog_device *wdd,
				unsigned int timeout_parm, struct device *dev)
{
	const char *dev_str = wdd->parent ? dev_name(wdd->parent) :
			      (const char *)wdd->info->identity;
	unsigned int t = 0;
	int ret = 0;

	watchdog_check_min_max_timeout(wdd);

	/* check the driver supplied value (likely a module parameter) first */
	if (timeout_parm) {
		if (!watchdog_timeout_invalid(wdd, timeout_parm)) {
			wdd->timeout = timeout_parm;
			return 0;
		}
		pr_err("%s: driver supplied timeout (%u) out of range\n",
			dev_str, timeout_parm);
		ret = -EINVAL;
	}

	/* try to get the timeout_sec property */
	if (dev && dev->of_node &&
	    of_property_read_u32(dev->of_node, "timeout-sec", &t) == 0) {
		if (t && !watchdog_timeout_invalid(wdd, t)) {
			wdd->timeout = t;
			return 0;
		}
		pr_err("%s: DT supplied timeout (%u) out of range\n", dev_str, t);
		ret = -EINVAL;
	}

	if (ret < 0 && wdd->timeout)
		pr_warn("%s: falling back to default timeout (%u)\n", dev_str,
			wdd->timeout);

	return ret;
}