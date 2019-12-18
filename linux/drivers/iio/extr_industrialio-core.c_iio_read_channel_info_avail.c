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
struct iio_dev_attr {int /*<<< orphan*/  address; int /*<<< orphan*/  c; } ;
struct iio_dev {TYPE_1__* info; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* read_avail ) (struct iio_dev*,int /*<<< orphan*/ ,int const**,int*,int*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_AVAIL_LIST 129 
#define  IIO_AVAIL_RANGE 128 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 int iio_format_avail_list (char*,int const*,int,int) ; 
 int iio_format_avail_range (char*,int const*,int) ; 
 int stub1 (struct iio_dev*,int /*<<< orphan*/ ,int const**,int*,int*,int /*<<< orphan*/ ) ; 
 struct iio_dev_attr* to_iio_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t iio_read_channel_info_avail(struct device *dev,
					   struct device_attribute *attr,
					   char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	const int *vals;
	int ret;
	int length;
	int type;

	ret = indio_dev->info->read_avail(indio_dev, this_attr->c,
					  &vals, &type, &length,
					  this_attr->address);

	if (ret < 0)
		return ret;
	switch (ret) {
	case IIO_AVAIL_LIST:
		return iio_format_avail_list(buf, vals, type, length);
	case IIO_AVAIL_RANGE:
		return iio_format_avail_range(buf, vals, type);
	default:
		return -EINVAL;
	}
}