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
 int /*<<< orphan*/  rdev_get_name (struct regulator_dev*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,void const*) ; 

__attribute__((used)) static int regulator_match(struct device *dev, const void *data)
{
	struct regulator_dev *r = dev_to_rdev(dev);

	return strcmp(rdev_get_name(r), data) == 0;
}