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
struct hid_driver {int /*<<< orphan*/  (* match ) (struct hid_device*,int /*<<< orphan*/ ) ;} ;
struct hid_device {int /*<<< orphan*/  status; struct hid_driver* driver; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_STAT_REPROBED ; 
 int device_reprobe (struct device*) ; 
 int /*<<< orphan*/  ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_ignore_special_drivers ; 
 int /*<<< orphan*/  stub1 (struct hid_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hid_device* to_hid_device (struct device*) ; 

__attribute__((used)) static int __hid_bus_reprobe_drivers(struct device *dev, void *data)
{
	struct hid_driver *hdrv = data;
	struct hid_device *hdev = to_hid_device(dev);

	if (hdev->driver == hdrv &&
	    !hdrv->match(hdev, hid_ignore_special_drivers) &&
	    !test_and_set_bit(ffs(HID_STAT_REPROBED), &hdev->status))
		return device_reprobe(dev);

	return 0;
}