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
typedef  int /*<<< orphan*/  u8 ;
struct st_lsm6dsx_sensor {struct st_lsm6dsx_hw* hw; } ;
struct st_lsm6dsx_hw {int /*<<< orphan*/  regmap; scalar_t__ enable_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_LSM6DSX_FIFO_ODR_MASK ; 
 int /*<<< orphan*/  ST_LSM6DSX_MAX_FIFO_ODR_VAL ; 
 int /*<<< orphan*/  ST_LSM6DSX_REG_FIFO_MODE_ADDR ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st_lsm6dsx_set_fifo_odr(struct st_lsm6dsx_sensor *sensor,
				   bool enable)
{
	struct st_lsm6dsx_hw *hw = sensor->hw;
	u8 data;

	data = hw->enable_mask ? ST_LSM6DSX_MAX_FIFO_ODR_VAL : 0;
	return regmap_update_bits(hw->regmap, ST_LSM6DSX_REG_FIFO_MODE_ADDR,
				 ST_LSM6DSX_FIFO_ODR_MASK,
				 FIELD_PREP(ST_LSM6DSX_FIFO_ODR_MASK, data));
}