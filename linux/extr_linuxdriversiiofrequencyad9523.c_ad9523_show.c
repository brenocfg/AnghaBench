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
typedef  int u32 ;
struct iio_dev_attr {scalar_t__ address; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ad9523_state {int /*<<< orphan*/  lock; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  AD9523_READBACK_0 ; 
 int ad9523_read (struct iio_dev*,int /*<<< orphan*/ ) ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct ad9523_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,int) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ad9523_show(struct device *dev,
			struct device_attribute *attr,
			char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	struct ad9523_state *st = iio_priv(indio_dev);
	int ret;

	mutex_lock(&st->lock);
	ret = ad9523_read(indio_dev, AD9523_READBACK_0);
	if (ret >= 0) {
		ret = sprintf(buf, "%d\n", !!(ret & (1 <<
			(u32)this_attr->address)));
	}
	mutex_unlock(&st->lock);

	return ret;
}