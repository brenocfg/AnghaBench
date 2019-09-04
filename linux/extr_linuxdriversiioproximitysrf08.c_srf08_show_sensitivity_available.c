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
struct srf08_data {TYPE_1__* chip_info; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int num_sensitivity_avail; int* sensitivity_avail; } ;

/* Variables and functions */
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct srf08_data* iio_priv (struct iio_dev*) ; 
 scalar_t__ sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t srf08_show_sensitivity_available(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	int i, len = 0;
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct srf08_data *data = iio_priv(indio_dev);

	for (i = 0; i < data->chip_info->num_sensitivity_avail; i++)
		if (data->chip_info->sensitivity_avail[i])
			len += sprintf(buf + len, "%d ",
				data->chip_info->sensitivity_avail[i]);

	len += sprintf(buf + len, "\n");

	return len;
}