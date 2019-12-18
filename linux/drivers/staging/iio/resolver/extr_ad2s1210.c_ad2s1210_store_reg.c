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
struct iio_dev_attr {unsigned char address; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ad2s1210_state {int /*<<< orphan*/  lock; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned char AD2S1210_MSB_IS_LOW ; 
 int EINVAL ; 
 int ad2s1210_config_write (struct ad2s1210_state*,unsigned char) ; 
 int /*<<< orphan*/  dev_to_iio_dev (struct device*) ; 
 struct ad2s1210_state* iio_priv (int /*<<< orphan*/ ) ; 
 int kstrtou8 (char const*,int,unsigned char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ad2s1210_store_reg(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t len)
{
	struct ad2s1210_state *st = iio_priv(dev_to_iio_dev(dev));
	unsigned char data;
	int ret;
	struct iio_dev_attr *iattr = to_iio_dev_attr(attr);

	ret = kstrtou8(buf, 10, &data);
	if (ret)
		return -EINVAL;
	mutex_lock(&st->lock);
	ret = ad2s1210_config_write(st, iattr->address);
	if (ret < 0)
		goto error_ret;
	ret = ad2s1210_config_write(st, data & AD2S1210_MSB_IS_LOW);
error_ret:
	mutex_unlock(&st->lock);
	return ret < 0 ? ret : len;
}