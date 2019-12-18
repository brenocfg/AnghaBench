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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct iio_chan_spec {int channel2; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_MOD_X 130 
#define  IIO_MOD_Y 129 
#define  IIO_MOD_Z 128 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  MMA9551_APPID_TILT ; 
 int MMA9551_TILT_ANGFLG ; 
 int /*<<< orphan*/  MMA9551_TILT_QUAD_REG ; 
 int /*<<< orphan*/  MMA9551_TILT_XY_ANG_REG ; 
 int MMA9551_TILT_XY_QUAD_SHIFT ; 
 int /*<<< orphan*/  MMA9551_TILT_XZ_ANG_REG ; 
 int MMA9551_TILT_XZ_QUAD_SHIFT ; 
 int /*<<< orphan*/  MMA9551_TILT_YZ_ANG_REG ; 
 int MMA9551_TILT_YZ_QUAD_SHIFT ; 
 int mma9551_read_status_byte (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int mma9551_set_power_state (struct i2c_client*,int) ; 

__attribute__((used)) static int mma9551_read_incli_chan(struct i2c_client *client,
				   const struct iio_chan_spec *chan,
				   int *val)
{
	u8 quad_shift, angle, quadrant;
	u16 reg_addr;
	int ret;

	switch (chan->channel2) {
	case IIO_MOD_X:
		reg_addr = MMA9551_TILT_YZ_ANG_REG;
		quad_shift = MMA9551_TILT_YZ_QUAD_SHIFT;
		break;
	case IIO_MOD_Y:
		reg_addr = MMA9551_TILT_XZ_ANG_REG;
		quad_shift = MMA9551_TILT_XZ_QUAD_SHIFT;
		break;
	case IIO_MOD_Z:
		reg_addr = MMA9551_TILT_XY_ANG_REG;
		quad_shift = MMA9551_TILT_XY_QUAD_SHIFT;
		break;
	default:
		return -EINVAL;
	}

	ret = mma9551_set_power_state(client, true);
	if (ret < 0)
		return ret;

	ret = mma9551_read_status_byte(client, MMA9551_APPID_TILT,
				       reg_addr, &angle);
	if (ret < 0)
		goto out_poweroff;

	ret = mma9551_read_status_byte(client, MMA9551_APPID_TILT,
				       MMA9551_TILT_QUAD_REG, &quadrant);
	if (ret < 0)
		goto out_poweroff;

	angle &= ~MMA9551_TILT_ANGFLG;
	quadrant = (quadrant >> quad_shift) & 0x03;

	if (quadrant == 1 || quadrant == 3)
		*val = 90 * (quadrant + 1) - angle;
	else
		*val = angle + 90 * quadrant;

	ret = IIO_VAL_INT;

out_poweroff:
	mma9551_set_power_state(client, false);
	return ret;
}