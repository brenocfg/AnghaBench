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
 int /*<<< orphan*/  device_unregister (struct device*) ; 
 int /*<<< orphan*/  nvdimm_bus_lock (struct device*) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

__attribute__((used)) static void nd_async_device_unregister(void *d, async_cookie_t cookie)
{
	struct device *dev = d;

	/* flush bus operations before delete */
	nvdimm_bus_lock(dev);
	nvdimm_bus_unlock(dev);

	device_unregister(dev);
	put_device(dev);
}