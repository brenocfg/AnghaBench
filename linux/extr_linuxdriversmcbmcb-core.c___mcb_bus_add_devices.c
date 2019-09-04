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
struct mcb_device {int is_added; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int device_attach (struct device*) ; 
 struct mcb_device* to_mcb_device (struct device*) ; 

__attribute__((used)) static int __mcb_bus_add_devices(struct device *dev, void *data)
{
	struct mcb_device *mdev = to_mcb_device(dev);
	int retval;

	if (mdev->is_added)
		return 0;

	retval = device_attach(dev);
	if (retval < 0)
		dev_err(dev, "Error adding device (%d)\n", retval);

	mdev->is_added = true;

	return 0;
}