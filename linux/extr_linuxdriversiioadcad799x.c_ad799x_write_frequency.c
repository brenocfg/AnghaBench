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
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ad799x_state {int /*<<< orphan*/  client; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  AD7998_CYCLE_TMR_REG ; 
 int AD7998_CYC_MASK ; 
 int ARRAY_SIZE (long*) ; 
 int EINVAL ; 
 long* ad7998_frequencies ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ad799x_state* iio_priv (struct iio_dev*) ; 
 int kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t ad799x_write_frequency(struct device *dev,
					 struct device_attribute *attr,
					 const char *buf,
					 size_t len)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad799x_state *st = iio_priv(indio_dev);

	long val;
	int ret, i;

	ret = kstrtol(buf, 10, &val);
	if (ret)
		return ret;

	mutex_lock(&indio_dev->mlock);
	ret = i2c_smbus_read_byte_data(st->client, AD7998_CYCLE_TMR_REG);
	if (ret < 0)
		goto error_ret_mutex;
	/* Wipe the bits clean */
	ret &= ~AD7998_CYC_MASK;

	for (i = 0; i < ARRAY_SIZE(ad7998_frequencies); i++)
		if (val == ad7998_frequencies[i])
			break;
	if (i == ARRAY_SIZE(ad7998_frequencies)) {
		ret = -EINVAL;
		goto error_ret_mutex;
	}

	ret = i2c_smbus_write_byte_data(st->client, AD7998_CYCLE_TMR_REG,
		ret | i);
	if (ret < 0)
		goto error_ret_mutex;
	ret = len;

error_ret_mutex:
	mutex_unlock(&indio_dev->mlock);

	return ret;
}