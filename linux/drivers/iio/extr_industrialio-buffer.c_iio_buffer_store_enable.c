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
struct iio_dev {int /*<<< orphan*/  mlock; int /*<<< orphan*/ * buffer; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int __iio_update_buffers (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 int iio_buffer_is_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int strtobool (char const*,int*) ; 

__attribute__((used)) static ssize_t iio_buffer_store_enable(struct device *dev,
				       struct device_attribute *attr,
				       const char *buf,
				       size_t len)
{
	int ret;
	bool requested_state;
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	bool inlist;

	ret = strtobool(buf, &requested_state);
	if (ret < 0)
		return ret;

	mutex_lock(&indio_dev->mlock);

	/* Find out if it is in the list */
	inlist = iio_buffer_is_active(indio_dev->buffer);
	/* Already in desired state */
	if (inlist == requested_state)
		goto done;

	if (requested_state)
		ret = __iio_update_buffers(indio_dev,
					 indio_dev->buffer, NULL);
	else
		ret = __iio_update_buffers(indio_dev,
					 NULL, indio_dev->buffer);

done:
	mutex_unlock(&indio_dev->mlock);
	return (ret < 0) ? ret : len;
}