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
struct hv_driver {int hvsock; } ;
struct hv_device {int /*<<< orphan*/  channel; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct hv_device* device_to_hv_device (struct device*) ; 
 struct hv_driver* drv_to_hv_drv (struct device_driver*) ; 
 scalar_t__ hv_vmbus_get_id (struct hv_driver*,struct hv_device*) ; 
 scalar_t__ is_hvsock_channel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmbus_match(struct device *device, struct device_driver *driver)
{
	struct hv_driver *drv = drv_to_hv_drv(driver);
	struct hv_device *hv_dev = device_to_hv_device(device);

	/* The hv_sock driver handles all hv_sock offers. */
	if (is_hvsock_channel(hv_dev->channel))
		return drv->hvsock;

	if (hv_vmbus_get_id(drv, hv_dev))
		return 1;

	return 0;
}