#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {int user_ctrl; scalar_t__ accl_fifo_enable; scalar_t__ gyro_fifo_enable; } ;
struct inv_mpu6050_state {TYPE_2__* reg; int /*<<< orphan*/  map; TYPE_1__ chip_config; scalar_t__ it_timestamp; } ;
struct iio_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  int_enable; int /*<<< orphan*/  fifo_en; int /*<<< orphan*/  user_ctrl; } ;

/* Variables and functions */
 int INV_MPU6050_BITS_GYRO_OUT ; 
 int INV_MPU6050_BIT_ACCEL_OUT ; 
 int INV_MPU6050_BIT_DATA_RDY_EN ; 
 int INV_MPU6050_BIT_FIFO_EN ; 
 int INV_MPU6050_BIT_FIFO_RST ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct inv_mpu6050_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regmap_get_device (int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int inv_reset_fifo(struct iio_dev *indio_dev)
{
	int result;
	u8 d;
	struct inv_mpu6050_state  *st = iio_priv(indio_dev);

	/* reset it timestamp validation */
	st->it_timestamp = 0;

	/* disable interrupt */
	result = regmap_write(st->map, st->reg->int_enable, 0);
	if (result) {
		dev_err(regmap_get_device(st->map), "int_enable failed %d\n",
			result);
		return result;
	}
	/* disable the sensor output to FIFO */
	result = regmap_write(st->map, st->reg->fifo_en, 0);
	if (result)
		goto reset_fifo_fail;
	/* disable fifo reading */
	result = regmap_write(st->map, st->reg->user_ctrl,
			      st->chip_config.user_ctrl);
	if (result)
		goto reset_fifo_fail;

	/* reset FIFO*/
	d = st->chip_config.user_ctrl | INV_MPU6050_BIT_FIFO_RST;
	result = regmap_write(st->map, st->reg->user_ctrl, d);
	if (result)
		goto reset_fifo_fail;

	/* enable interrupt */
	if (st->chip_config.accl_fifo_enable ||
	    st->chip_config.gyro_fifo_enable) {
		result = regmap_write(st->map, st->reg->int_enable,
				      INV_MPU6050_BIT_DATA_RDY_EN);
		if (result)
			return result;
	}
	/* enable FIFO reading */
	d = st->chip_config.user_ctrl | INV_MPU6050_BIT_FIFO_EN;
	result = regmap_write(st->map, st->reg->user_ctrl, d);
	if (result)
		goto reset_fifo_fail;
	/* enable sensor output to FIFO */
	d = 0;
	if (st->chip_config.gyro_fifo_enable)
		d |= INV_MPU6050_BITS_GYRO_OUT;
	if (st->chip_config.accl_fifo_enable)
		d |= INV_MPU6050_BIT_ACCEL_OUT;
	result = regmap_write(st->map, st->reg->fifo_en, d);
	if (result)
		goto reset_fifo_fail;

	return 0;

reset_fifo_fail:
	dev_err(regmap_get_device(st->map), "reset fifo failed %d\n", result);
	result = regmap_write(st->map, st->reg->int_enable,
			      INV_MPU6050_BIT_DATA_RDY_EN);

	return result;
}