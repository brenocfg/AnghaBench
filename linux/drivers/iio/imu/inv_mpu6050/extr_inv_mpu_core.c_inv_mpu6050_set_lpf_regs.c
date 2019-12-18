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
struct inv_mpu6050_state {int chip_type; TYPE_1__* reg; int /*<<< orphan*/  map; } ;
typedef  enum inv_mpu6050_filter_e { ____Placeholder_inv_mpu6050_filter_e } inv_mpu6050_filter_e ;
struct TYPE_2__ {int /*<<< orphan*/  accel_lpf; int /*<<< orphan*/  lpf; } ;

/* Variables and functions */
#define  INV_MPU6000 130 
#define  INV_MPU6050 129 
#define  INV_MPU9150 128 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int inv_mpu6050_set_lpf_regs(struct inv_mpu6050_state *st,
				    enum inv_mpu6050_filter_e val)
{
	int result;

	result = regmap_write(st->map, st->reg->lpf, val);
	if (result)
		return result;

	switch (st->chip_type) {
	case INV_MPU6050:
	case INV_MPU6000:
	case INV_MPU9150:
		/* old chips, nothing to do */
		result = 0;
		break;
	default:
		/* set accel lpf */
		result = regmap_write(st->map, st->reg->accel_lpf, val);
		break;
	}

	return result;
}