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
struct input_polled_dev {TYPE_2__* input; scalar_t__ devres_managed; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_input_polldev_match ; 
 int /*<<< orphan*/  devm_input_polldev_unregister ; 
 int /*<<< orphan*/  devres_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct input_polled_dev*) ; 
 int /*<<< orphan*/  input_unregister_device (TYPE_2__*) ; 

void input_unregister_polled_device(struct input_polled_dev *dev)
{
	if (dev->devres_managed)
		WARN_ON(devres_destroy(dev->input->dev.parent,
					devm_input_polldev_unregister,
					devm_input_polldev_match,
					dev));

	input_unregister_device(dev->input);
}