#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct st_lsm6dsx_sensor {int id; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  enum st_lsm6dsx_sensor_id { ____Placeholder_st_lsm6dsx_sensor_id } st_lsm6dsx_sensor_id ;
struct TYPE_4__ {TYPE_1__* fs_avl; } ;
struct TYPE_3__ {int /*<<< orphan*/  gain; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int ST_LSM6DSX_FS_LIST_SIZE ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 struct st_lsm6dsx_sensor* iio_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ scnprintf (char*,scalar_t__,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* st_lsm6dsx_fs_table ; 

__attribute__((used)) static ssize_t st_lsm6dsx_sysfs_scale_avail(struct device *dev,
					    struct device_attribute *attr,
					    char *buf)
{
	struct st_lsm6dsx_sensor *sensor = iio_priv(dev_get_drvdata(dev));
	enum st_lsm6dsx_sensor_id id = sensor->id;
	int i, len = 0;

	for (i = 0; i < ST_LSM6DSX_FS_LIST_SIZE; i++)
		len += scnprintf(buf + len, PAGE_SIZE - len, "0.%06u ",
				 st_lsm6dsx_fs_table[id].fs_avl[i].gain);
	buf[len - 1] = '\n';

	return len;
}