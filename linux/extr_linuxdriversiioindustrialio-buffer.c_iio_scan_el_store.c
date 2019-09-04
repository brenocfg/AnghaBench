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
struct iio_dev_attr {int /*<<< orphan*/  address; } ;
struct iio_dev {int /*<<< orphan*/  mlock; struct iio_buffer* buffer; } ;
struct iio_buffer {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 scalar_t__ iio_buffer_is_active (struct iio_buffer*) ; 
 int iio_scan_mask_clear (struct iio_buffer*,int /*<<< orphan*/ ) ; 
 int iio_scan_mask_query (struct iio_dev*,struct iio_buffer*,int /*<<< orphan*/ ) ; 
 int iio_scan_mask_set (struct iio_dev*,struct iio_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int strtobool (char const*,int*) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t iio_scan_el_store(struct device *dev,
				 struct device_attribute *attr,
				 const char *buf,
				 size_t len)
{
	int ret;
	bool state;
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct iio_buffer *buffer = indio_dev->buffer;
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);

	ret = strtobool(buf, &state);
	if (ret < 0)
		return ret;
	mutex_lock(&indio_dev->mlock);
	if (iio_buffer_is_active(indio_dev->buffer)) {
		ret = -EBUSY;
		goto error_ret;
	}
	ret = iio_scan_mask_query(indio_dev, buffer, this_attr->address);
	if (ret < 0)
		goto error_ret;
	if (!state && ret) {
		ret = iio_scan_mask_clear(buffer, this_attr->address);
		if (ret)
			goto error_ret;
	} else if (state && !ret) {
		ret = iio_scan_mask_set(indio_dev, buffer, this_attr->address);
		if (ret)
			goto error_ret;
	}

error_ret:
	mutex_unlock(&indio_dev->mlock);

	return ret < 0 ? ret : len;

}