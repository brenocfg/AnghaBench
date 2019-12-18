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
struct input_polled_devres {struct input_polled_dev* polldev; } ;
struct input_polled_dev {int devres_managed; TYPE_2__* input; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device* parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_input_polldev_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct input_polled_devres*) ; 
 struct input_polled_devres* devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct input_polled_devres*) ; 
 struct input_polled_dev* input_allocate_polled_device () ; 

struct input_polled_dev *devm_input_allocate_polled_device(struct device *dev)
{
	struct input_polled_dev *polldev;
	struct input_polled_devres *devres;

	devres = devres_alloc(devm_input_polldev_release, sizeof(*devres),
			      GFP_KERNEL);
	if (!devres)
		return NULL;

	polldev = input_allocate_polled_device();
	if (!polldev) {
		devres_free(devres);
		return NULL;
	}

	polldev->input->dev.parent = dev;
	polldev->devres_managed = true;

	devres->polldev = polldev;
	devres_add(dev, devres);

	return polldev;
}