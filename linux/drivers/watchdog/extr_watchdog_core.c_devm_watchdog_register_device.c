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
struct watchdog_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_watchdog_unregister_device ; 
 int /*<<< orphan*/  devres_add (struct device*,struct watchdog_device**) ; 
 struct watchdog_device** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct watchdog_device**) ; 
 int watchdog_register_device (struct watchdog_device*) ; 

int devm_watchdog_register_device(struct device *dev,
				struct watchdog_device *wdd)
{
	struct watchdog_device **rcwdd;
	int ret;

	rcwdd = devres_alloc(devm_watchdog_unregister_device, sizeof(*rcwdd),
			     GFP_KERNEL);
	if (!rcwdd)
		return -ENOMEM;

	ret = watchdog_register_device(wdd);
	if (!ret) {
		*rcwdd = wdd;
		devres_add(dev, rcwdd);
	} else {
		devres_free(rcwdd);
	}

	return ret;
}