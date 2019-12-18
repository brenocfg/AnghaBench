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
typedef  int u16 ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ad7816_chip_info {scalar_t__ channel_id; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 int AD7816_TEMP_FLOAT_MASK ; 
 int AD7816_TEMP_FLOAT_OFFSET ; 
 int AD7816_VALUE_OFFSET ; 
 int BIT (int) ; 
 int /*<<< orphan*/  EIO ; 
 int ad7816_spi_read (struct ad7816_chip_info*,int*) ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct ad7816_chip_info* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 

__attribute__((used)) static ssize_t ad7816_show_value(struct device *dev,
				 struct device_attribute *attr,
				 char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad7816_chip_info *chip = iio_priv(indio_dev);
	u16 data;
	s8 value;
	int ret;

	ret = ad7816_spi_read(chip, &data);
	if (ret)
		return -EIO;

	data >>= AD7816_VALUE_OFFSET;

	if (chip->channel_id == 0) {
		value = (s8)((data >> AD7816_TEMP_FLOAT_OFFSET) - 103);
		data &= AD7816_TEMP_FLOAT_MASK;
		if (value < 0)
			data = BIT(AD7816_TEMP_FLOAT_OFFSET) - data;
		return sprintf(buf, "%d.%.2d\n", value, data * 25);
	}
	return sprintf(buf, "%u\n", data);
}