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
struct bmg160_data {int /*<<< orphan*/  mutex; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  raw_val ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  BMG160_AXIS_TO_REG (int) ; 
 int IIO_VAL_INT ; 
 int bmg160_set_power_state (struct bmg160_data*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int sign_extend32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bmg160_get_axis(struct bmg160_data *data, int axis, int *val)
{
	struct device *dev = regmap_get_device(data->regmap);
	int ret;
	__le16 raw_val;

	mutex_lock(&data->mutex);
	ret = bmg160_set_power_state(data, true);
	if (ret < 0) {
		mutex_unlock(&data->mutex);
		return ret;
	}

	ret = regmap_bulk_read(data->regmap, BMG160_AXIS_TO_REG(axis), &raw_val,
			       sizeof(raw_val));
	if (ret < 0) {
		dev_err(dev, "Error reading axis %d\n", axis);
		bmg160_set_power_state(data, false);
		mutex_unlock(&data->mutex);
		return ret;
	}

	*val = sign_extend32(le16_to_cpu(raw_val), 15);
	ret = bmg160_set_power_state(data, false);
	mutex_unlock(&data->mutex);
	if (ret < 0)
		return ret;

	return IIO_VAL_INT;
}