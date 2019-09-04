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
 int ENODEV ; 
 int EPROBE_DEFER ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  deferred_probe_timeout ; 
 int /*<<< orphan*/  dev_WARN (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 scalar_t__ initcalls_done ; 

int driver_deferred_probe_check_state(struct device *dev)
{
	if (initcalls_done) {
		if (!deferred_probe_timeout) {
			dev_WARN(dev, "deferred probe timeout, ignoring dependency");
			return -ETIMEDOUT;
		}
		dev_warn(dev, "ignoring dependency for device, assuming no driver");
		return -ENODEV;
	}
	return -EPROBE_DEFER;
}