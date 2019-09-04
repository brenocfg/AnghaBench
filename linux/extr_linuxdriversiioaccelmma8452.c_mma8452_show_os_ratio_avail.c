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
typedef  scalar_t__ u16 ;
struct mma8452_data {int dummy; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__**) ; 
 scalar_t__ PAGE_SIZE ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct mma8452_data* iio_priv (struct iio_dev*) ; 
 int mma8452_get_odr_index (struct mma8452_data*) ; 
 scalar_t__** mma8452_os_ratio ; 
 scalar_t__ scnprintf (char*,scalar_t__,char*,scalar_t__) ; 

__attribute__((used)) static ssize_t mma8452_show_os_ratio_avail(struct device *dev,
					   struct device_attribute *attr,
					   char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct mma8452_data *data = iio_priv(indio_dev);
	int i = mma8452_get_odr_index(data);
	int j;
	u16 val = 0;
	size_t len = 0;

	for (j = 0; j < ARRAY_SIZE(mma8452_os_ratio); j++) {
		if (val == mma8452_os_ratio[j][i])
			continue;

		val = mma8452_os_ratio[j][i];

		len += scnprintf(buf + len, PAGE_SIZE - len, "%d ", val);
	}
	buf[len - 1] = '\n';

	return len;
}