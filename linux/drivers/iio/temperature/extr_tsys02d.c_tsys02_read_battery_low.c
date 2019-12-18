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
struct ms_ht_dev {int dummy; } ;
struct iio_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct ms_ht_dev* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  ms_sensors_show_battery_low (struct ms_ht_dev*,char*) ; 

__attribute__((used)) static ssize_t tsys02_read_battery_low(struct device *dev,
				       struct device_attribute *attr,
				       char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct ms_ht_dev *dev_data = iio_priv(indio_dev);

	return ms_sensors_show_battery_low(dev_data, buf);
}