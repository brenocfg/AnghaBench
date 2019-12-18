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
struct iio_dev_attr {int /*<<< orphan*/  c; } ;
struct iio_dev {TYPE_1__* info; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* write_event_value ) (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 int /*<<< orphan*/  iio_ev_attr_dir (struct iio_dev_attr*) ; 
 int /*<<< orphan*/  iio_ev_attr_info (struct iio_dev_attr*) ; 
 int /*<<< orphan*/  iio_ev_attr_type (struct iio_dev_attr*) ; 
 int iio_str_to_fixpoint (char const*,int,int*,int*) ; 
 int stub1 (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t iio_ev_value_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf,
				  size_t len)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	int val, val2;
	int ret;

	if (!indio_dev->info->write_event_value)
		return -EINVAL;

	ret = iio_str_to_fixpoint(buf, 100000, &val, &val2);
	if (ret)
		return ret;
	ret = indio_dev->info->write_event_value(indio_dev,
		this_attr->c, iio_ev_attr_type(this_attr),
		iio_ev_attr_dir(this_attr), iio_ev_attr_info(this_attr),
		val, val2);
	if (ret < 0)
		return ret;

	return len;
}