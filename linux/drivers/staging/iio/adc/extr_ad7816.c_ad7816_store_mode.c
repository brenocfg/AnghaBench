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
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ad7816_chip_info {int /*<<< orphan*/  mode; int /*<<< orphan*/  rdwr_pin; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  AD7816_FULL ; 
 int /*<<< orphan*/  AD7816_PD ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 struct ad7816_chip_info* iio_priv (struct iio_dev*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static ssize_t ad7816_store_mode(struct device *dev,
				 struct device_attribute *attr,
				 const char *buf,
				 size_t len)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad7816_chip_info *chip = iio_priv(indio_dev);

	if (strcmp(buf, "full")) {
		gpiod_set_value(chip->rdwr_pin, 1);
		chip->mode = AD7816_FULL;
	} else {
		gpiod_set_value(chip->rdwr_pin, 0);
		chip->mode = AD7816_PD;
	}

	return len;
}