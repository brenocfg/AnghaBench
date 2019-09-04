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
struct TYPE_2__ {int /*<<< orphan*/  completion; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 int __device_suspend_late (struct device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  async_schedule (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  async_suspend_late ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 scalar_t__ is_async (struct device*) ; 
 int /*<<< orphan*/  pm_transition ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int device_suspend_late(struct device *dev)
{
	reinit_completion(&dev->power.completion);

	if (is_async(dev)) {
		get_device(dev);
		async_schedule(async_suspend_late, dev);
		return 0;
	}

	return __device_suspend_late(dev, pm_transition, false);
}