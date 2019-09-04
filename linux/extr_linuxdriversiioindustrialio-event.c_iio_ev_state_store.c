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
struct TYPE_2__ {int (* write_event_config ) (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 int /*<<< orphan*/  iio_ev_attr_dir (struct iio_dev_attr*) ; 
 int /*<<< orphan*/  iio_ev_attr_type (struct iio_dev_attr*) ; 
 int strtobool (char const*,int*) ; 
 int stub1 (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t iio_ev_state_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf,
				  size_t len)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	int ret;
	bool val;

	ret = strtobool(buf, &val);
	if (ret < 0)
		return ret;

	ret = indio_dev->info->write_event_config(indio_dev,
		this_attr->c, iio_ev_attr_type(this_attr),
		iio_ev_attr_dir(this_attr), val);

	return (ret < 0) ? ret : len;
}