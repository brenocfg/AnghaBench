#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iio_dev {int /*<<< orphan*/  mlock; struct iio_buffer* buffer; } ;
struct iio_buffer {unsigned int length; unsigned int watermark; TYPE_1__* access; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_length ) (struct iio_buffer*,unsigned int) ;} ;

/* Variables and functions */
 int EBUSY ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 scalar_t__ iio_buffer_is_active (struct iio_buffer*) ; 
 int kstrtouint (char const*,int,unsigned int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct iio_buffer*,unsigned int) ; 

__attribute__((used)) static ssize_t iio_buffer_write_length(struct device *dev,
				       struct device_attribute *attr,
				       const char *buf, size_t len)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct iio_buffer *buffer = indio_dev->buffer;
	unsigned int val;
	int ret;

	ret = kstrtouint(buf, 10, &val);
	if (ret)
		return ret;

	if (val == buffer->length)
		return len;

	mutex_lock(&indio_dev->mlock);
	if (iio_buffer_is_active(indio_dev->buffer)) {
		ret = -EBUSY;
	} else {
		buffer->access->set_length(buffer, val);
		ret = 0;
	}
	if (ret)
		goto out;
	if (buffer->length && buffer->length < buffer->watermark)
		buffer->watermark = buffer->length;
out:
	mutex_unlock(&indio_dev->mlock);

	return ret ? ret : len;
}