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
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 struct tsl2772_chip* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tsl2772_chip_off (struct iio_dev*) ; 

__attribute__((used)) static int tsl2772_suspend(struct device *dev)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct tsl2772_chip *chip = iio_priv(indio_dev);
	int ret;

	ret = tsl2772_chip_off(indio_dev);
	regulator_bulk_disable(ARRAY_SIZE(chip->supplies), chip->supplies);

	return ret;
}