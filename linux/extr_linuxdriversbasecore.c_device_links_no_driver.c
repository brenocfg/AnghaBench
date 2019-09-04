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
 int /*<<< orphan*/  __device_links_no_driver (struct device*) ; 
 int /*<<< orphan*/  device_links_write_lock () ; 
 int /*<<< orphan*/  device_links_write_unlock () ; 

void device_links_no_driver(struct device *dev)
{
	device_links_write_lock();
	__device_links_no_driver(dev);
	device_links_write_unlock();
}