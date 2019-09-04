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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct st_lsm6dsx_sensor {size_t id; struct st_lsm6dsx_hw* hw; } ;
struct st_lsm6dsx_reg {int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;
struct st_lsm6dsx_hw {int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {struct st_lsm6dsx_reg reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_LSM6DSX_SHIFT_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int st_lsm6dsx_check_odr (struct st_lsm6dsx_sensor*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* st_lsm6dsx_odr_table ; 

__attribute__((used)) static int st_lsm6dsx_set_odr(struct st_lsm6dsx_sensor *sensor, u16 odr)
{
	struct st_lsm6dsx_hw *hw = sensor->hw;
	const struct st_lsm6dsx_reg *reg;
	int err;
	u8 val;

	err = st_lsm6dsx_check_odr(sensor, odr, &val);
	if (err < 0)
		return err;

	reg = &st_lsm6dsx_odr_table[sensor->id].reg;
	return regmap_update_bits(hw->regmap, reg->addr, reg->mask,
				  ST_LSM6DSX_SHIFT_VAL(val, reg->mask));
}