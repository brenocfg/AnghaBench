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
struct srf08_data {int sensitivity; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct srf08_data* iio_priv (struct iio_dev*) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t srf08_show_sensitivity(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct srf08_data *data = iio_priv(indio_dev);
	int len;

	len = sprintf(buf, "%d\n", data->sensitivity);

	return len;
}