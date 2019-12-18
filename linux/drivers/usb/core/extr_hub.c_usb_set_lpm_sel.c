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
struct usb_device {struct usb_device* parent; } ;
struct usb3_lpm_parameters {unsigned int pel; unsigned int sel; } ;

/* Variables and functions */

__attribute__((used)) static void usb_set_lpm_sel(struct usb_device *udev,
		struct usb3_lpm_parameters *udev_lpm_params)
{
	struct usb_device *parent;
	unsigned int num_hubs;
	unsigned int total_sel;

	/* t1 = device PEL */
	total_sel = udev_lpm_params->pel;
	/* How many external hubs are in between the device & the root port. */
	for (parent = udev->parent, num_hubs = 0; parent->parent;
			parent = parent->parent)
		num_hubs++;
	/* t2 = 2.1us + 250ns * (num_hubs - 1) */
	if (num_hubs > 0)
		total_sel += 2100 + 250 * (num_hubs - 1);

	/* t4 = 250ns * num_hubs */
	total_sel += 250 * num_hubs;

	udev_lpm_params->sel = total_sel;
}