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
struct tsl2772_chip {int /*<<< orphan*/  supplies; } ;
struct iio_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSL2772_BOOT_MAX_SLEEP_TIME ; 
 int /*<<< orphan*/  TSL2772_BOOT_MIN_SLEEP_TIME ; 
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 struct tsl2772_chip* iio_priv (struct iio_dev*) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tsl2772_chip_on (struct iio_dev*) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tsl2772_resume(struct device *dev)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct tsl2772_chip *chip = iio_priv(indio_dev);
	int ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(chip->supplies), chip->supplies);
	if (ret < 0)
		return ret;

	usleep_range(TSL2772_BOOT_MIN_SLEEP_TIME, TSL2772_BOOT_MAX_SLEEP_TIME);

	return tsl2772_chip_on(indio_dev);
}