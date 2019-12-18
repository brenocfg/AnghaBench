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
struct device {int dummy; } ;
struct bmc150_accel_data {int /*<<< orphan*/  mutex; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMC150_ACCEL_REG_TEMP ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int sign_extend32 (unsigned int,int) ; 

__attribute__((used)) static int bmc150_accel_get_temp(struct bmc150_accel_data *data, int *val)
{
	struct device *dev = regmap_get_device(data->regmap);
	int ret;
	unsigned int value;

	mutex_lock(&data->mutex);

	ret = regmap_read(data->regmap, BMC150_ACCEL_REG_TEMP, &value);
	if (ret < 0) {
		dev_err(dev, "Error reading reg_temp\n");
		mutex_unlock(&data->mutex);
		return ret;
	}
	*val = sign_extend32(value, 7);

	mutex_unlock(&data->mutex);

	return IIO_VAL_INT;
}