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
typedef  int /*<<< orphan*/  u32 ;
struct iio_dev_attr {int /*<<< orphan*/  address; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ad9523_state {int /*<<< orphan*/  lock; } ;
typedef  int ssize_t ;

/* Variables and functions */
#define  AD9523_EEPROM 129 
#define  AD9523_SYNC 128 
 int ENODEV ; 
 int ad9523_store_eeprom (struct iio_dev*) ; 
 int ad9523_sync (struct iio_dev*) ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct ad9523_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int strtobool (char const*,int*) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ad9523_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t len)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	struct ad9523_state *st = iio_priv(indio_dev);
	bool state;
	int ret;

	ret = strtobool(buf, &state);
	if (ret < 0)
		return ret;

	if (!state)
		return len;

	mutex_lock(&st->lock);
	switch ((u32)this_attr->address) {
	case AD9523_SYNC:
		ret = ad9523_sync(indio_dev);
		break;
	case AD9523_EEPROM:
		ret = ad9523_store_eeprom(indio_dev);
		break;
	default:
		ret = -ENODEV;
	}
	mutex_unlock(&st->lock);

	return ret ? ret : len;
}