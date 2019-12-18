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
typedef  scalar_t__ u16 ;
struct TYPE_6__ {struct st_lsm6dsx_ext_dev_settings* settings; } ;
struct st_lsm6dsx_sensor {TYPE_3__ ext_info; } ;
struct TYPE_5__ {TYPE_1__* odr_avl; } ;
struct st_lsm6dsx_ext_dev_settings {TYPE_2__ odr_table; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_4__ {scalar_t__ hz; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int ST_LSM6DSX_ODR_LIST_SIZE ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 struct st_lsm6dsx_sensor* iio_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ scnprintf (char*,scalar_t__,char*,scalar_t__) ; 

__attribute__((used)) static ssize_t
st_lsm6dsx_shub_sampling_freq_avail(struct device *dev,
				    struct device_attribute *attr,
				    char *buf)
{
	struct st_lsm6dsx_sensor *sensor = iio_priv(dev_get_drvdata(dev));
	const struct st_lsm6dsx_ext_dev_settings *settings;
	int i, len = 0;

	settings = sensor->ext_info.settings;
	for (i = 0; i < ST_LSM6DSX_ODR_LIST_SIZE; i++) {
		u16 val = settings->odr_table.odr_avl[i].hz;

		if (val > 0)
			len += scnprintf(buf + len, PAGE_SIZE - len, "%d ",
					 val);
	}
	buf[len - 1] = '\n';

	return len;
}