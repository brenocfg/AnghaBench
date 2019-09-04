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
struct tsc200x {int /*<<< orphan*/  vio; } ;
struct device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 struct tsc200x* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsc200x_attr_group ; 

int tsc200x_remove(struct device *dev)
{
	struct tsc200x *ts = dev_get_drvdata(dev);

	sysfs_remove_group(&dev->kobj, &tsc200x_attr_group);

	regulator_disable(ts->vio);

	return 0;
}