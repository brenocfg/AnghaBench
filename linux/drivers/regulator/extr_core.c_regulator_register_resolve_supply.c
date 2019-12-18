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
struct regulator_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct regulator_dev* dev_to_rdev (struct device*) ; 
 int /*<<< orphan*/  rdev_dbg (struct regulator_dev*,char*) ; 
 scalar_t__ regulator_resolve_supply (struct regulator_dev*) ; 

__attribute__((used)) static int regulator_register_resolve_supply(struct device *dev, void *data)
{
	struct regulator_dev *rdev = dev_to_rdev(dev);

	if (regulator_resolve_supply(rdev))
		rdev_dbg(rdev, "unable to resolve supply\n");

	return 0;
}