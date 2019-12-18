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
struct iio_dev {int /*<<< orphan*/  mlock; TYPE_1__* buffer; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int scan_timestamp; } ;

/* Variables and functions */
 int EBUSY ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 scalar_t__ iio_buffer_is_active (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int strtobool (char const*,int*) ; 

__attribute__((used)) static ssize_t iio_scan_el_ts_store(struct device *dev,
				    struct device_attribute *attr,
				    const char *buf,
				    size_t len)
{
	int ret;
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	bool state;

	ret = strtobool(buf, &state);
	if (ret < 0)
		return ret;

	mutex_lock(&indio_dev->mlock);
	if (iio_buffer_is_active(indio_dev->buffer)) {
		ret = -EBUSY;
		goto error_ret;
	}
	indio_dev->buffer->scan_timestamp = state;
error_ret:
	mutex_unlock(&indio_dev->mlock);

	return ret ? ret : len;
}