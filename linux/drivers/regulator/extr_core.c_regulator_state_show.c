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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  _regulator_is_enabled (struct regulator_dev*) ; 
 struct regulator_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  regulator_lock (struct regulator_dev*) ; 
 int /*<<< orphan*/  regulator_print_state (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_unlock (struct regulator_dev*) ; 

__attribute__((used)) static ssize_t regulator_state_show(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	struct regulator_dev *rdev = dev_get_drvdata(dev);
	ssize_t ret;

	regulator_lock(rdev);
	ret = regulator_print_state(buf, _regulator_is_enabled(rdev));
	regulator_unlock(rdev);

	return ret;
}