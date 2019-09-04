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
struct tsc200x {int /*<<< orphan*/  mutex; int /*<<< orphan*/  regmap; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 unsigned int MAX_12BIT ; 
 int /*<<< orphan*/  TSC200X_REG_TEMP_HIGH ; 
 int /*<<< orphan*/  __tsc200x_disable (struct tsc200x*) ; 
 int /*<<< orphan*/  __tsc200x_enable (struct tsc200x*) ; 
 struct tsc200x* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,unsigned int,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  tsc200x_reset (struct tsc200x*) ; 

__attribute__((used)) static ssize_t tsc200x_selftest_show(struct device *dev,
				     struct device_attribute *attr,
				     char *buf)
{
	struct tsc200x *ts = dev_get_drvdata(dev);
	unsigned int temp_high;
	unsigned int temp_high_orig;
	unsigned int temp_high_test;
	bool success = true;
	int error;

	mutex_lock(&ts->mutex);

	/*
	 * Test TSC200X communications via temp high register.
	 */
	__tsc200x_disable(ts);

	error = regmap_read(ts->regmap, TSC200X_REG_TEMP_HIGH, &temp_high_orig);
	if (error) {
		dev_warn(dev, "selftest failed: read error %d\n", error);
		success = false;
		goto out;
	}

	temp_high_test = (temp_high_orig - 1) & MAX_12BIT;

	error = regmap_write(ts->regmap, TSC200X_REG_TEMP_HIGH, temp_high_test);
	if (error) {
		dev_warn(dev, "selftest failed: write error %d\n", error);
		success = false;
		goto out;
	}

	error = regmap_read(ts->regmap, TSC200X_REG_TEMP_HIGH, &temp_high);
	if (error) {
		dev_warn(dev, "selftest failed: read error %d after write\n",
			 error);
		success = false;
		goto out;
	}

	if (temp_high != temp_high_test) {
		dev_warn(dev, "selftest failed: %d != %d\n",
			 temp_high, temp_high_test);
		success = false;
	}

	/* hardware reset */
	tsc200x_reset(ts);

	if (!success)
		goto out;

	/* test that the reset really happened */
	error = regmap_read(ts->regmap, TSC200X_REG_TEMP_HIGH, &temp_high);
	if (error) {
		dev_warn(dev, "selftest failed: read error %d after reset\n",
			 error);
		success = false;
		goto out;
	}

	if (temp_high != temp_high_orig) {
		dev_warn(dev, "selftest failed after reset: %d != %d\n",
			 temp_high, temp_high_orig);
		success = false;
	}

out:
	__tsc200x_enable(ts);
	mutex_unlock(&ts->mutex);

	return sprintf(buf, "%d\n", success);
}