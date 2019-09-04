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
typedef  unsigned int u32 ;
struct inv_mpu6050_state {TYPE_1__* reg; int /*<<< orphan*/  map; } ;
struct TYPE_2__ {int /*<<< orphan*/  pwr_mgmt_1; int /*<<< orphan*/  pwr_mgmt_2; } ;

/* Variables and functions */
 unsigned int INV_CLK_INTERNAL ; 
 unsigned int INV_CLK_PLL ; 
 unsigned int INV_MPU6050_BIT_CLK_MASK ; 
 unsigned int INV_MPU6050_BIT_PWR_GYRO_STBY ; 
 int /*<<< orphan*/  INV_MPU6050_TEMP_UP_TIME ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

int inv_mpu6050_switch_engine(struct inv_mpu6050_state *st, bool en, u32 mask)
{
	unsigned int d, mgmt_1;
	int result;
	/*
	 * switch clock needs to be careful. Only when gyro is on, can
	 * clock source be switched to gyro. Otherwise, it must be set to
	 * internal clock
	 */
	if (mask == INV_MPU6050_BIT_PWR_GYRO_STBY) {
		result = regmap_read(st->map, st->reg->pwr_mgmt_1, &mgmt_1);
		if (result)
			return result;

		mgmt_1 &= ~INV_MPU6050_BIT_CLK_MASK;
	}

	if ((mask == INV_MPU6050_BIT_PWR_GYRO_STBY) && (!en)) {
		/*
		 * turning off gyro requires switch to internal clock first.
		 * Then turn off gyro engine
		 */
		mgmt_1 |= INV_CLK_INTERNAL;
		result = regmap_write(st->map, st->reg->pwr_mgmt_1, mgmt_1);
		if (result)
			return result;
	}

	result = regmap_read(st->map, st->reg->pwr_mgmt_2, &d);
	if (result)
		return result;
	if (en)
		d &= ~mask;
	else
		d |= mask;
	result = regmap_write(st->map, st->reg->pwr_mgmt_2, d);
	if (result)
		return result;

	if (en) {
		/* Wait for output to stabilize */
		msleep(INV_MPU6050_TEMP_UP_TIME);
		if (mask == INV_MPU6050_BIT_PWR_GYRO_STBY) {
			/* switch internal clock to PLL */
			mgmt_1 |= INV_CLK_PLL;
			result = regmap_write(st->map,
					      st->reg->pwr_mgmt_1, mgmt_1);
			if (result)
				return result;
		}
	}

	return 0;
}