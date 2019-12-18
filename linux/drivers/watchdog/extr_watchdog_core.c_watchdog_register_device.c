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
struct watchdog_device {TYPE_1__* info; scalar_t__ parent; } ;
struct TYPE_2__ {scalar_t__ identity; } ;

/* Variables and functions */
 int __watchdog_register_device (struct watchdog_device*) ; 
 char const* dev_name (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,int) ; 
 int /*<<< orphan*/  watchdog_deferred_registration_add (struct watchdog_device*) ; 
 scalar_t__ wtd_deferred_reg_done ; 
 int /*<<< orphan*/  wtd_deferred_reg_mutex ; 

int watchdog_register_device(struct watchdog_device *wdd)
{
	const char *dev_str;
	int ret = 0;

	mutex_lock(&wtd_deferred_reg_mutex);
	if (wtd_deferred_reg_done)
		ret = __watchdog_register_device(wdd);
	else
		watchdog_deferred_registration_add(wdd);
	mutex_unlock(&wtd_deferred_reg_mutex);

	if (ret) {
		dev_str = wdd->parent ? dev_name(wdd->parent) :
			  (const char *)wdd->info->identity;
		pr_err("%s: failed to register watchdog device (err = %d)\n",
			dev_str, ret);
	}

	return ret;
}