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
struct st_lsm6dsx_sensor {size_t id; struct st_lsm6dsx_hw* hw; } ;
struct st_lsm6dsx_hw {TYPE_1__* settings; } ;
struct st_lsm6dsx_fs_table_entry {int fs_len; TYPE_2__* fs_avl; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  gain; } ;
struct TYPE_3__ {struct st_lsm6dsx_fs_table_entry* fs_table; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 struct st_lsm6dsx_sensor* iio_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ scnprintf (char*,scalar_t__,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t st_lsm6dsx_sysfs_scale_avail(struct device *dev,
					    struct device_attribute *attr,
					    char *buf)
{
	struct st_lsm6dsx_sensor *sensor = iio_priv(dev_get_drvdata(dev));
	const struct st_lsm6dsx_fs_table_entry *fs_table;
	struct st_lsm6dsx_hw *hw = sensor->hw;
	int i, len = 0;

	fs_table = &hw->settings->fs_table[sensor->id];
	for (i = 0; i < fs_table->fs_len; i++)
		len += scnprintf(buf + len, PAGE_SIZE - len, "0.%06u ",
				 fs_table->fs_avl[i].gain);
	buf[len - 1] = '\n';

	return len;
}