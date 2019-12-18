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
struct device {struct device* parent; } ;
struct uwb_dev {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct uwb_dev*) ; 
 int device_add (struct device*) ; 

__attribute__((used)) static int __uwb_dev_sys_add(struct uwb_dev *uwb_dev, struct device *parent_dev)
{
	struct device *dev;

	dev = &uwb_dev->dev;
	dev->parent = parent_dev;
	dev_set_drvdata(dev, uwb_dev);

	return device_add(dev);
}