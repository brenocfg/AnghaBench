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
 int /*<<< orphan*/  device_hotplug_lock ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void unlock_device_hotplug(void)
{
	mutex_unlock(&device_hotplug_lock);
}