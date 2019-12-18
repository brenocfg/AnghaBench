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
struct device {int /*<<< orphan*/ * bus; int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct rpmsg_device {struct device dev; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_register (struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  rpmsg_bus ; 

int rpmsg_register_device(struct rpmsg_device *rpdev)
{
	struct device *dev = &rpdev->dev;
	int ret;

	dev_set_name(&rpdev->dev, "%s.%s.%d.%d", dev_name(dev->parent),
		     rpdev->id.name, rpdev->src, rpdev->dst);

	rpdev->dev.bus = &rpmsg_bus;

	ret = device_register(&rpdev->dev);
	if (ret) {
		dev_err(dev, "device_register failed: %d\n", ret);
		put_device(&rpdev->dev);
	}

	return ret;
}