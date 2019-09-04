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
struct iio_trigger {int dummy; } ;
struct iio_dev {int dummy; } ;
struct bmc150_magn_data {int dready_trigger_on; int /*<<< orphan*/  mutex; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMC150_MAGN_MASK_DRDY_EN ; 
 int /*<<< orphan*/  BMC150_MAGN_REG_INT_DRDY ; 
 int BMC150_MAGN_SHIFT_DRDY_EN ; 
 int bmc150_magn_reset_intr (struct bmc150_magn_data*) ; 
 struct bmc150_magn_data* iio_priv (struct iio_dev*) ; 
 struct iio_dev* iio_trigger_get_drvdata (struct iio_trigger*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bmc150_magn_data_rdy_trigger_set_state(struct iio_trigger *trig,
						  bool state)
{
	struct iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	struct bmc150_magn_data *data = iio_priv(indio_dev);
	int ret = 0;

	mutex_lock(&data->mutex);
	if (state == data->dready_trigger_on)
		goto err_unlock;

	ret = regmap_update_bits(data->regmap, BMC150_MAGN_REG_INT_DRDY,
				 BMC150_MAGN_MASK_DRDY_EN,
				 state << BMC150_MAGN_SHIFT_DRDY_EN);
	if (ret < 0)
		goto err_unlock;

	data->dready_trigger_on = state;

	if (state) {
		ret = bmc150_magn_reset_intr(data);
		if (ret < 0)
			goto err_unlock;
	}
	mutex_unlock(&data->mutex);

	return 0;

err_unlock:
	mutex_unlock(&data->mutex);
	return ret;
}