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
struct mma9551_data {int* event_enabled; int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
typedef  enum mma9551_tilt_axis { ____Placeholder_mma9551_tilt_axis } mma9551_tilt_axis ;
typedef  enum mma9551_gpio_pin { ____Placeholder_mma9551_gpio_pin } mma9551_gpio_pin ;
typedef  enum iio_modifier { ____Placeholder_iio_modifier } iio_modifier ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_MOD_X 130 
#define  IIO_MOD_Y 129 
#define  IIO_MOD_Z 128 
 int /*<<< orphan*/  MMA9551_APPID_NONE ; 
 int /*<<< orphan*/  MMA9551_APPID_TILT ; 
 int MMA9551_TILT_XY_ANG_REG ; 
 int MMA9551_TILT_XZ_ANG_REG ; 
 int MMA9551_TILT_YZ_ANG_REG ; 
 struct mma9551_data* iio_priv (struct iio_dev*) ; 
 int mma9551_gpio_config (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mma9551_set_power_state (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mma9551_config_incli_event(struct iio_dev *indio_dev,
				      enum iio_modifier axis,
				      int state)
{
	struct mma9551_data *data = iio_priv(indio_dev);
	enum mma9551_tilt_axis mma_axis;
	int ret;

	/* IIO counts axes from 1, because IIO_NO_MOD is 0. */
	mma_axis = axis - 1;

	if (data->event_enabled[mma_axis] == state)
		return 0;

	if (state == 0) {
		ret = mma9551_gpio_config(data->client,
					  (enum mma9551_gpio_pin)mma_axis,
					  MMA9551_APPID_NONE, 0, 0);
		if (ret < 0)
			return ret;

		ret = mma9551_set_power_state(data->client, false);
		if (ret < 0)
			return ret;
	} else {
		int bitnum;

		/* Bit 7 of each angle register holds the angle flag. */
		switch (axis) {
		case IIO_MOD_X:
			bitnum = 7 + 8 * MMA9551_TILT_YZ_ANG_REG;
			break;
		case IIO_MOD_Y:
			bitnum = 7 + 8 * MMA9551_TILT_XZ_ANG_REG;
			break;
		case IIO_MOD_Z:
			bitnum = 7 + 8 * MMA9551_TILT_XY_ANG_REG;
			break;
		default:
			return -EINVAL;
		}


		ret = mma9551_set_power_state(data->client, true);
		if (ret < 0)
			return ret;

		ret = mma9551_gpio_config(data->client,
					  (enum mma9551_gpio_pin)mma_axis,
					  MMA9551_APPID_TILT, bitnum, 0);
		if (ret < 0) {
			mma9551_set_power_state(data->client, false);
			return ret;
		}
	}

	data->event_enabled[mma_axis] = state;

	return ret;
}