#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hif_device_usb {int /*<<< orphan*/  fw_done; TYPE_1__* udev; } ;
struct device {struct device* parent; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_release_driver (struct device*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 

__attribute__((used)) static void ath9k_hif_usb_firmware_fail(struct hif_device_usb *hif_dev)
{
	struct device *dev = &hif_dev->udev->dev;
	struct device *parent = dev->parent;

	complete_all(&hif_dev->fw_done);

	if (parent)
		device_lock(parent);

	device_release_driver(dev);

	if (parent)
		device_unlock(parent);
}