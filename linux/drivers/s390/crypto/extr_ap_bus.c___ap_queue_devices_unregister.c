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
 int /*<<< orphan*/  device_unregister (struct device*) ; 
 scalar_t__ is_queue_dev (struct device*) ; 

__attribute__((used)) static int __ap_queue_devices_unregister(struct device *dev, void *dummy)
{
	if (is_queue_dev(dev))
		device_unregister(dev);
	return 0;
}