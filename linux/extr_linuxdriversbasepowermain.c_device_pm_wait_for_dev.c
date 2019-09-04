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
struct TYPE_2__ {int /*<<< orphan*/  async_suspend; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 int async_error ; 
 int /*<<< orphan*/  dpm_wait (struct device*,int /*<<< orphan*/ ) ; 

int device_pm_wait_for_dev(struct device *subordinate, struct device *dev)
{
	dpm_wait(dev, subordinate->power.async_suspend);
	return async_error;
}