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
struct ad9834_state {scalar_t__ devid; int control; int /*<<< orphan*/  lock; int /*<<< orphan*/  msg; int /*<<< orphan*/  spi; int /*<<< orphan*/  data; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int AD9834_MODE ; 
 int AD9834_OPBITEN ; 
 int AD9834_REG_CMD ; 
 int EINVAL ; 
 scalar_t__ ID_AD9833 ; 
 scalar_t__ ID_AD9837 ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct ad9834_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int spi_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_streq (char const*,char*) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ad9834_store_wavetype(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf,
				     size_t len)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ad9834_state *st = iio_priv(indio_dev);
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	int ret = 0;
	bool is_ad9833_7 = (st->devid == ID_AD9833) || (st->devid == ID_AD9837);

	mutex_lock(&st->lock);

	switch ((u32)this_attr->address) {
	case 0:
		if (sysfs_streq(buf, "sine")) {
			st->control &= ~AD9834_MODE;
			if (is_ad9833_7)
				st->control &= ~AD9834_OPBITEN;
		} else if (sysfs_streq(buf, "triangle")) {
			if (is_ad9833_7) {
				st->control &= ~AD9834_OPBITEN;
				st->control |= AD9834_MODE;
			} else if (st->control & AD9834_OPBITEN) {
				ret = -EINVAL;	/* AD9843 reserved mode */
			} else {
				st->control |= AD9834_MODE;
			}
		} else if (is_ad9833_7 && sysfs_streq(buf, "square")) {
			st->control &= ~AD9834_MODE;
			st->control |= AD9834_OPBITEN;
		} else {
			ret = -EINVAL;
		}

		break;
	case 1:
		if (sysfs_streq(buf, "square") &&
		    !(st->control & AD9834_MODE)) {
			st->control &= ~AD9834_MODE;
			st->control |= AD9834_OPBITEN;
		} else {
			ret = -EINVAL;
		}
		break;
	default:
		ret = -EINVAL;
		break;
	}

	if (!ret) {
		st->data = cpu_to_be16(AD9834_REG_CMD | st->control);
		ret = spi_sync(st->spi, &st->msg);
	}
	mutex_unlock(&st->lock);

	return ret ? ret : len;
}