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
struct input_devres {struct input_dev* input; } ;
struct TYPE_2__ {struct device* parent; } ;
struct input_dev {int devres_managed; TYPE_1__ dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_input_device_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct input_devres*) ; 
 struct input_devres* devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct input_devres*) ; 
 struct input_dev* input_allocate_device () ; 

struct input_dev *devm_input_allocate_device(struct device *dev)
{
	struct input_dev *input;
	struct input_devres *devres;

	devres = devres_alloc(devm_input_device_release,
			      sizeof(*devres), GFP_KERNEL);
	if (!devres)
		return NULL;

	input = input_allocate_device();
	if (!input) {
		devres_free(devres);
		return NULL;
	}

	input->dev.parent = dev;
	input->devres_managed = true;

	devres->input = input;
	devres_add(dev, devres);

	return input;
}