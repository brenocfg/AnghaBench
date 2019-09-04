#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct st_sensor_data {TYPE_3__* sensor_settings; } ;
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_5__ {TYPE_1__* odr_avl; } ;
struct TYPE_6__ {TYPE_2__ odr; } ;
struct TYPE_4__ {scalar_t__ hz; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int ST_SENSORS_ODR_LIST_MAX ; 
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 struct st_sensor_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ scnprintf (char*,scalar_t__,char*,scalar_t__) ; 

ssize_t st_sensors_sysfs_sampling_frequency_avail(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	int i, len = 0;
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct st_sensor_data *sdata = iio_priv(indio_dev);

	mutex_lock(&indio_dev->mlock);
	for (i = 0; i < ST_SENSORS_ODR_LIST_MAX; i++) {
		if (sdata->sensor_settings->odr.odr_avl[i].hz == 0)
			break;

		len += scnprintf(buf + len, PAGE_SIZE - len, "%d ",
				sdata->sensor_settings->odr.odr_avl[i].hz);
	}
	mutex_unlock(&indio_dev->mlock);
	buf[len - 1] = '\n';

	return len;
}