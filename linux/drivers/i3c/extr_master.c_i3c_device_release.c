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
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct i3c_device {TYPE_1__ dev; int /*<<< orphan*/  desc; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct i3c_device* dev_to_i3cdev (struct device*) ; 
 int /*<<< orphan*/  kfree (struct i3c_device*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i3c_device_release(struct device *dev)
{
	struct i3c_device *i3cdev = dev_to_i3cdev(dev);

	WARN_ON(i3cdev->desc);

	of_node_put(i3cdev->dev.of_node);
	kfree(i3cdev);
}