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
struct mxc4005_data {int trigger_enabled; int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct iio_trigger {int dummy; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MXC4005_REG_INT_MASK1 ; 
 int /*<<< orphan*/  MXC4005_REG_INT_MASK1_BIT_DRDYE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct mxc4005_data* iio_priv (struct iio_dev*) ; 
 struct iio_dev* iio_trigger_get_drvdata (struct iio_trigger*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mxc4005_set_trigger_state(struct iio_trigger *trig,
				     bool state)
{
	struct iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	struct mxc4005_data *data = iio_priv(indio_dev);
	int ret;

	mutex_lock(&data->mutex);
	if (state) {
		ret = regmap_write(data->regmap, MXC4005_REG_INT_MASK1,
				   MXC4005_REG_INT_MASK1_BIT_DRDYE);
	} else {
		ret = regmap_write(data->regmap, MXC4005_REG_INT_MASK1,
				   ~MXC4005_REG_INT_MASK1_BIT_DRDYE);
	}

	if (ret < 0) {
		mutex_unlock(&data->mutex);
		dev_err(data->dev, "failed to update reg_int_mask1");
		return ret;
	}

	data->trigger_enabled = state;
	mutex_unlock(&data->mutex);

	return 0;
}