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
struct inv_mpu6050_state {int irq_mask; size_t chip_type; int /*<<< orphan*/  chip_period; int /*<<< orphan*/  chip_config; TYPE_1__* reg; int /*<<< orphan*/  map; } ;
struct inv_mpu6050_chip_config {int dummy; } ;
struct iio_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  config; } ;
struct TYPE_3__ {int /*<<< orphan*/  int_pin_cfg; int /*<<< orphan*/  accl_config; int /*<<< orphan*/  sample_rate_div; int /*<<< orphan*/  gyro_config; } ;

/* Variables and functions */
 int INV_MPU6050_ACCL_CONFIG_FSR_SHIFT ; 
 int INV_MPU6050_FIFO_RATE_TO_DIVIDER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INV_MPU6050_FILTER_20HZ ; 
 int INV_MPU6050_FSR_2000DPS ; 
 int INV_MPU6050_FS_02G ; 
 int INV_MPU6050_GYRO_CONFIG_FSR_SHIFT ; 
 int /*<<< orphan*/  INV_MPU6050_INIT_FIFO_RATE ; 
 int /*<<< orphan*/  NSEC_PER_MSEC ; 
 TYPE_2__* hw_info ; 
 struct inv_mpu6050_state* iio_priv (struct iio_dev*) ; 
 int inv_mpu6050_set_lpf_regs (struct inv_mpu6050_state*,int /*<<< orphan*/ ) ; 
 int inv_mpu6050_set_power_itg (struct inv_mpu6050_state*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int inv_mpu6050_init_config(struct iio_dev *indio_dev)
{
	int result;
	u8 d;
	struct inv_mpu6050_state *st = iio_priv(indio_dev);

	result = inv_mpu6050_set_power_itg(st, true);
	if (result)
		return result;
	d = (INV_MPU6050_FSR_2000DPS << INV_MPU6050_GYRO_CONFIG_FSR_SHIFT);
	result = regmap_write(st->map, st->reg->gyro_config, d);
	if (result)
		goto error_power_off;

	result = inv_mpu6050_set_lpf_regs(st, INV_MPU6050_FILTER_20HZ);
	if (result)
		goto error_power_off;

	d = INV_MPU6050_FIFO_RATE_TO_DIVIDER(INV_MPU6050_INIT_FIFO_RATE);
	result = regmap_write(st->map, st->reg->sample_rate_div, d);
	if (result)
		goto error_power_off;

	d = (INV_MPU6050_FS_02G << INV_MPU6050_ACCL_CONFIG_FSR_SHIFT);
	result = regmap_write(st->map, st->reg->accl_config, d);
	if (result)
		goto error_power_off;

	result = regmap_write(st->map, st->reg->int_pin_cfg, st->irq_mask);
	if (result)
		return result;

	memcpy(&st->chip_config, hw_info[st->chip_type].config,
	       sizeof(struct inv_mpu6050_chip_config));

	/*
	 * Internal chip period is 1ms (1kHz).
	 * Let's use at the beginning the theorical value before measuring
	 * with interrupt timestamps.
	 */
	st->chip_period = NSEC_PER_MSEC;

	return inv_mpu6050_set_power_itg(st, false);

error_power_off:
	inv_mpu6050_set_power_itg(st, false);
	return result;
}