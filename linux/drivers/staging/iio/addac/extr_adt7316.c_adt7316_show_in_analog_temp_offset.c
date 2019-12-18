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
struct adt7316_chip_info {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADT7316_IN_ANALOG_TEMP_OFFSET ; 
 int /*<<< orphan*/  adt7316_show_temp_offset (struct adt7316_chip_info*,int /*<<< orphan*/ ,char*) ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct adt7316_chip_info* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static ssize_t adt7316_show_in_analog_temp_offset(struct device *dev,
						  struct device_attribute *attr,
						  char *buf)
{
	struct iio_dev *dev_info = dev_to_iio_dev(dev);
	struct adt7316_chip_info *chip = iio_priv(dev_info);

	return adt7316_show_temp_offset(chip,
			ADT7316_IN_ANALOG_TEMP_OFFSET, buf);
}