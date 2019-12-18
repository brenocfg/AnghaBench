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
typedef  int u8 ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ad7746_chip_info {int config; int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  AD7746_REG_CFG ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ad7746_chip_info* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int strtobool (char const*,int*) ; 

__attribute__((used)) static inline ssize_t ad7746_start_calib(struct device *dev,
					 struct device_attribute *attr,
					 const char *buf,
					 size_t len,
					 u8 regval)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad7746_chip_info *chip = iio_priv(indio_dev);
	int ret, timeout = 10;
	bool doit;

	ret = strtobool(buf, &doit);
	if (ret < 0)
		return ret;

	if (!doit)
		return 0;

	mutex_lock(&chip->lock);
	regval |= chip->config;
	ret = i2c_smbus_write_byte_data(chip->client, AD7746_REG_CFG, regval);
	if (ret < 0)
		goto unlock;

	do {
		msleep(20);
		ret = i2c_smbus_read_byte_data(chip->client, AD7746_REG_CFG);
		if (ret < 0)
			goto unlock;

	} while ((ret == regval) && timeout--);

	mutex_unlock(&chip->lock);

	return len;

unlock:
	mutex_unlock(&chip->lock);
	return ret;
}