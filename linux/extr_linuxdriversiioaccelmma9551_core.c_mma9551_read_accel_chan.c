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
typedef  int /*<<< orphan*/  u16 ;
struct iio_chan_spec {int channel2; } ;
struct i2c_client {int dummy; } ;
typedef  int s16 ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_MOD_X 130 
#define  IIO_MOD_Y 129 
#define  IIO_MOD_Z 128 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  MMA9551_AFE_X_ACCEL_REG ; 
 int /*<<< orphan*/  MMA9551_AFE_Y_ACCEL_REG ; 
 int /*<<< orphan*/  MMA9551_AFE_Z_ACCEL_REG ; 
 int /*<<< orphan*/  MMA9551_APPID_AFE ; 
 int mma9551_read_status_word (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int mma9551_set_power_state (struct i2c_client*,int) ; 

int mma9551_read_accel_chan(struct i2c_client *client,
			    const struct iio_chan_spec *chan,
			    int *val, int *val2)
{
	u16 reg_addr;
	s16 raw_accel;
	int ret;

	switch (chan->channel2) {
	case IIO_MOD_X:
		reg_addr = MMA9551_AFE_X_ACCEL_REG;
		break;
	case IIO_MOD_Y:
		reg_addr = MMA9551_AFE_Y_ACCEL_REG;
		break;
	case IIO_MOD_Z:
		reg_addr = MMA9551_AFE_Z_ACCEL_REG;
		break;
	default:
		return -EINVAL;
	}

	ret = mma9551_set_power_state(client, true);
	if (ret < 0)
		return ret;

	ret = mma9551_read_status_word(client, MMA9551_APPID_AFE,
				       reg_addr, &raw_accel);
	if (ret < 0)
		goto out_poweroff;

	*val = raw_accel;

	ret = IIO_VAL_INT;

out_poweroff:
	mma9551_set_power_state(client, false);
	return ret;
}