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
 int device_links_read_lock () ; 
 int /*<<< orphan*/  device_links_read_unlock (int) ; 
 int /*<<< orphan*/  device_pm_lock () ; 
 int /*<<< orphan*/  device_pm_unlock () ; 
 int /*<<< orphan*/  device_reorder_to_tail (struct device*,int /*<<< orphan*/ *) ; 

void device_pm_move_to_tail(struct device *dev)
{
	int idx;

	idx = device_links_read_lock();
	device_pm_lock();
	device_reorder_to_tail(dev, NULL);
	device_pm_unlock();
	device_links_read_unlock(idx);
}