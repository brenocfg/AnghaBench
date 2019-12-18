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
struct st_lsm6dsx_sensor {int id; struct st_lsm6dsx_hw* hw; } ;
struct st_lsm6dsx_hw {TYPE_3__* settings; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  enum st_lsm6dsx_sensor_id { ____Placeholder_st_lsm6dsx_sensor_id } st_lsm6dsx_sensor_id ;
struct TYPE_6__ {TYPE_2__* odr_table; } ;
struct TYPE_5__ {TYPE_1__* odr_avl; } ;
struct TYPE_4__ {int /*<<< orphan*/  hz; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int ST_LSM6DSX_ODR_LIST_SIZE ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 struct st_lsm6dsx_sensor* iio_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ scnprintf (char*,scalar_t__,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
st_lsm6dsx_sysfs_sampling_frequency_avail(struct device *dev,
					  struct device_attribute *attr,
					  char *buf)
{
	struct st_lsm6dsx_sensor *sensor = iio_priv(dev_get_drvdata(dev));
	enum st_lsm6dsx_sensor_id id = sensor->id;
	struct st_lsm6dsx_hw *hw = sensor->hw;
	int i, len = 0;

	for (i = 0; i < ST_LSM6DSX_ODR_LIST_SIZE; i++)
		len += scnprintf(buf + len, PAGE_SIZE - len, "%d ",
				 hw->settings->odr_table[id].odr_avl[i].hz);
	buf[len - 1] = '\n';

	return len;
}