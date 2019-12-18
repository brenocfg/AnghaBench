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
struct fxas21002c_data {int /*<<< orphan*/  lock; int /*<<< orphan*/ * regmap_fields; int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 size_t F_TEMP ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int fxas21002c_pm_get (struct fxas21002c_data*) ; 
 int fxas21002c_pm_put (struct fxas21002c_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_field_read (int /*<<< orphan*/ ,unsigned int*) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int sign_extend32 (unsigned int,int) ; 

__attribute__((used)) static int fxas21002c_temp_get(struct fxas21002c_data *data, int *val)
{
	struct device *dev = regmap_get_device(data->regmap);
	unsigned int temp;
	int ret;

	mutex_lock(&data->lock);
	ret = fxas21002c_pm_get(data);
	if (ret < 0)
		goto data_unlock;

	ret = regmap_field_read(data->regmap_fields[F_TEMP], &temp);
	if (ret < 0) {
		dev_err(dev, "failed to read temp: %d\n", ret);
		goto data_unlock;
	}

	*val = sign_extend32(temp, 7);

	ret = fxas21002c_pm_put(data);
	if (ret < 0)
		goto data_unlock;

	ret = IIO_VAL_INT;

data_unlock:
	mutex_unlock(&data->lock);

	return ret;
}