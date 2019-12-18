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
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* class_find_device_by_of_node (int /*<<< orphan*/ *,struct device_node*) ; 
 struct regulator_dev* dev_to_rdev (struct device*) ; 
 int /*<<< orphan*/  regulator_class ; 

struct regulator_dev *of_find_regulator_by_node(struct device_node *np)
{
	struct device *dev;

	dev = class_find_device_by_of_node(&regulator_class, np);

	return dev ? dev_to_rdev(dev) : NULL;
}