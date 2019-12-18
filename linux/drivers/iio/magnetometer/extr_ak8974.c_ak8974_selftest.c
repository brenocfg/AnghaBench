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
struct device {int dummy; } ;
struct ak8974 {int /*<<< orphan*/  map; TYPE_1__* i2c; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK8974_CTRL3 ; 
 int /*<<< orphan*/  AK8974_CTRL3_SELFTEST ; 
 int /*<<< orphan*/  AK8974_SELFTEST ; 
 int /*<<< orphan*/  AK8974_SELFTEST_DELAY ; 
 unsigned int AK8974_SELFTEST_IDLE ; 
 unsigned int AK8974_SELFTEST_OK ; 
 int EIO ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ak8974_selftest(struct ak8974 *ak8974)
{
	struct device *dev = &ak8974->i2c->dev;
	unsigned int val;
	int ret;

	ret = regmap_read(ak8974->map, AK8974_SELFTEST, &val);
	if (ret)
		return ret;
	if (val != AK8974_SELFTEST_IDLE) {
		dev_err(dev, "selftest not idle before test\n");
		return -EIO;
	}

	/* Trigger self-test */
	ret = regmap_update_bits(ak8974->map,
			AK8974_CTRL3,
			AK8974_CTRL3_SELFTEST,
			AK8974_CTRL3_SELFTEST);
	if (ret) {
		dev_err(dev, "could not write CTRL3\n");
		return ret;
	}

	msleep(AK8974_SELFTEST_DELAY);

	ret = regmap_read(ak8974->map, AK8974_SELFTEST, &val);
	if (ret)
		return ret;
	if (val != AK8974_SELFTEST_OK) {
		dev_err(dev, "selftest result NOT OK (%02x)\n", val);
		return -EIO;
	}

	ret = regmap_read(ak8974->map, AK8974_SELFTEST, &val);
	if (ret)
		return ret;
	if (val != AK8974_SELFTEST_IDLE) {
		dev_err(dev, "selftest not idle after test (%02x)\n", val);
		return -EIO;
	}
	dev_dbg(dev, "passed self-test\n");

	return 0;
}