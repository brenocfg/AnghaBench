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
struct iio_dev {int /*<<< orphan*/  mlock; struct iio_buffer* buffer; } ;
struct iio_buffer {unsigned int length; unsigned int watermark; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 scalar_t__ iio_buffer_is_active (struct iio_buffer*) ; 
 int kstrtouint (char const*,int,unsigned int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t iio_buffer_store_watermark(struct device *dev,
					  struct device_attribute *attr,
					  const char *buf,
					  size_t len)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct iio_buffer *buffer = indio_dev->buffer;
	unsigned int val;
	int ret;

	ret = kstrtouint(buf, 10, &val);
	if (ret)
		return ret;
	if (!val)
		return -EINVAL;

	mutex_lock(&indio_dev->mlock);

	if (val > buffer->length) {
		ret = -EINVAL;
		goto out;
	}

	if (iio_buffer_is_active(indio_dev->buffer)) {
		ret = -EBUSY;
		goto out;
	}

	buffer->watermark = val;
out:
	mutex_unlock(&indio_dev->mlock);

	return ret ? ret : len;
}