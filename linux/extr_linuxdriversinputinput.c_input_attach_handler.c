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
struct input_handler {int (* connect ) (struct input_handler*,struct input_dev*,struct input_device_id const*) ;int /*<<< orphan*/  name; } ;
struct input_device_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct input_dev {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENODEV ; 
 struct input_device_id* input_match_device (struct input_handler*,struct input_dev*) ; 
 int /*<<< orphan*/  kobject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct input_handler*,struct input_dev*,struct input_device_id const*) ; 

__attribute__((used)) static int input_attach_handler(struct input_dev *dev, struct input_handler *handler)
{
	const struct input_device_id *id;
	int error;

	id = input_match_device(handler, dev);
	if (!id)
		return -ENODEV;

	error = handler->connect(handler, dev, id);
	if (error && error != -ENODEV)
		pr_err("failed to attach handler %s to device %s, error: %d\n",
		       handler->name, kobject_name(&dev->dev.kobj), error);

	return error;
}