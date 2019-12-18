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
 int /*<<< orphan*/  device_for_each_child_reverse (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resume_lpss_device ; 

int intel_lpss_prepare(struct device *dev)
{
	/*
	 * Resume both child devices before entering system sleep. This
	 * ensures that they are in proper state before they get suspended.
	 */
	device_for_each_child_reverse(dev, NULL, resume_lpss_device);
	return 0;
}