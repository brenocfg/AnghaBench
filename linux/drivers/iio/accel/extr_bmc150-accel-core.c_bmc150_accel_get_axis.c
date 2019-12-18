#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int shift; scalar_t__ realbits; } ;
struct iio_chan_spec {int scan_index; TYPE_1__ scan_type; } ;
struct device {int dummy; } ;
struct bmc150_accel_data {int /*<<< orphan*/  mutex; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  raw_val ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  BMC150_ACCEL_AXIS_TO_REG (int) ; 
 int IIO_VAL_INT ; 
 int bmc150_accel_set_power_state (struct bmc150_accel_data*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct device* regmap_get_device (int /*<<< orphan*/ ) ; 
 int sign_extend32 (int,scalar_t__) ; 

__attribute__((used)) static int bmc150_accel_get_axis(struct bmc150_accel_data *data,
				 struct iio_chan_spec const *chan,
				 int *val)
{
	struct device *dev = regmap_get_device(data->regmap);
	int ret;
	int axis = chan->scan_index;
	__le16 raw_val;

	mutex_lock(&data->mutex);
	ret = bmc150_accel_set_power_state(data, true);
	if (ret < 0) {
		mutex_unlock(&data->mutex);
		return ret;
	}

	ret = regmap_bulk_read(data->regmap, BMC150_ACCEL_AXIS_TO_REG(axis),
			       &raw_val, sizeof(raw_val));
	if (ret < 0) {
		dev_err(dev, "Error reading axis %d\n", axis);
		bmc150_accel_set_power_state(data, false);
		mutex_unlock(&data->mutex);
		return ret;
	}
	*val = sign_extend32(le16_to_cpu(raw_val) >> chan->scan_type.shift,
			     chan->scan_type.realbits - 1);
	ret = bmc150_accel_set_power_state(data, false);
	mutex_unlock(&data->mutex);
	if (ret < 0)
		return ret;

	return IIO_VAL_INT;
}