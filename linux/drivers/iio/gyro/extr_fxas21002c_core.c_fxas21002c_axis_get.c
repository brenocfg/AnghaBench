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
struct fxas21002c_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  axis_be ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  FXAS21002C_AXIS_TO_REG (int) ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int) ; 
 int fxas21002c_pm_get (struct fxas21002c_data*) ; 
 int fxas21002c_pm_put (struct fxas21002c_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int sign_extend32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fxas21002c_axis_get(struct fxas21002c_data *data,
			       int index, int *val)
{
	struct device *dev = regmap_get_device(data->regmap);
	__be16 axis_be;
	int ret;

	mutex_lock(&data->lock);
	ret = fxas21002c_pm_get(data);
	if (ret < 0)
		goto data_unlock;

	ret = regmap_bulk_read(data->regmap, FXAS21002C_AXIS_TO_REG(index),
			       &axis_be, sizeof(axis_be));
	if (ret < 0) {
		dev_err(dev, "failed to read axis: %d: %d\n", index, ret);
		goto data_unlock;
	}

	*val = sign_extend32(be16_to_cpu(axis_be), 15);

	ret = fxas21002c_pm_put(data);
	if (ret < 0)
		goto data_unlock;

	ret = IIO_VAL_INT;

data_unlock:
	mutex_unlock(&data->lock);

	return ret;
}