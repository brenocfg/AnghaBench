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
typedef  int /*<<< orphan*/  u32 ;
struct inv_mpu6050_state {int /*<<< orphan*/  lock; int /*<<< orphan*/  irq_mask; TYPE_1__* reg; int /*<<< orphan*/  map; } ;
struct iio_dev {int dummy; } ;
struct i2c_mux_core {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  int_pin_cfg; } ;

/* Variables and functions */
 struct iio_dev* i2c_mux_priv (struct i2c_mux_core*) ; 
 struct inv_mpu6050_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  inv_mpu6050_set_power_itg (struct inv_mpu6050_state*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inv_mpu6050_deselect_bypass(struct i2c_mux_core *muxc, u32 chan_id)
{
	struct iio_dev *indio_dev = i2c_mux_priv(muxc);
	struct inv_mpu6050_state *st = iio_priv(indio_dev);

	mutex_lock(&st->lock);

	/* It doesn't really matter if any of the calls fail */
	regmap_write(st->map, st->reg->int_pin_cfg, st->irq_mask);
	inv_mpu6050_set_power_itg(st, false);

	mutex_unlock(&st->lock);

	return 0;
}