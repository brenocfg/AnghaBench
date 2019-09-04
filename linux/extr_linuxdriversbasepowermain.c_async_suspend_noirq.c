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
typedef  int /*<<< orphan*/  async_cookie_t ;

/* Variables and functions */
 int __device_suspend_noirq (struct device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dpm_save_failed_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_dev_err (struct device*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pm_transition ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

__attribute__((used)) static void async_suspend_noirq(void *data, async_cookie_t cookie)
{
	struct device *dev = (struct device *)data;
	int error;

	error = __device_suspend_noirq(dev, pm_transition, true);
	if (error) {
		dpm_save_failed_dev(dev_name(dev));
		pm_dev_err(dev, pm_transition, " async", error);
	}

	put_device(dev);
}