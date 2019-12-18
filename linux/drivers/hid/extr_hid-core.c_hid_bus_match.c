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
struct hid_driver {int dummy; } ;
struct hid_device {int dummy; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * hid_match_device (struct hid_device*,struct hid_driver*) ; 
 struct hid_device* to_hid_device (struct device*) ; 
 struct hid_driver* to_hid_driver (struct device_driver*) ; 

__attribute__((used)) static int hid_bus_match(struct device *dev, struct device_driver *drv)
{
	struct hid_driver *hdrv = to_hid_driver(drv);
	struct hid_device *hdev = to_hid_device(dev);

	return hid_match_device(hdev, hdrv) != NULL;
}