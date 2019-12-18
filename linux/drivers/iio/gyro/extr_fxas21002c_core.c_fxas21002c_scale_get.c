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
struct fxas21002c_data {int /*<<< orphan*/  lock; int /*<<< orphan*/ * regmap_fields; } ;

/* Variables and functions */
 size_t F_FS ; 
 int fxas21002c_range_fs_from_value (struct fxas21002c_data*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_field_read (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int fxas21002c_scale_get(struct fxas21002c_data *data, int *val)
{
	int fs_bits;
	int scale;
	int ret;

	mutex_lock(&data->lock);
	ret = regmap_field_read(data->regmap_fields[F_FS], &fs_bits);
	if (ret < 0)
		goto data_unlock;

	scale = fxas21002c_range_fs_from_value(data, fs_bits);
	if (scale < 0) {
		ret = scale;
		goto data_unlock;
	}

	*val = scale;

data_unlock:
	mutex_unlock(&data->lock);

	return ret;
}