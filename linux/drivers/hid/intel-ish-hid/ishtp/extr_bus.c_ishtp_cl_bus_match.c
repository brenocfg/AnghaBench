#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ishtp_cl_driver {int /*<<< orphan*/  guid; } ;
struct ishtp_cl_device {TYPE_2__* fw_client; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  protocol_name; } ;
struct TYPE_4__ {TYPE_1__ props; } ;

/* Variables and functions */
 int guid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ishtp_cl_device* to_ishtp_cl_device (struct device*) ; 
 struct ishtp_cl_driver* to_ishtp_cl_driver (struct device_driver*) ; 

__attribute__((used)) static int ishtp_cl_bus_match(struct device *dev, struct device_driver *drv)
{
	struct ishtp_cl_device *device = to_ishtp_cl_device(dev);
	struct ishtp_cl_driver *driver = to_ishtp_cl_driver(drv);

	return guid_equal(driver->guid,
			  &device->fw_client->props.protocol_name);
}