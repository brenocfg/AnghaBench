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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct st_lsm6dsx_sensor {size_t id; scalar_t__ gain; struct st_lsm6dsx_hw* hw; } ;
struct st_lsm6dsx_reg {int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;
struct st_lsm6dsx_hw {int /*<<< orphan*/  regmap; } ;
struct TYPE_4__ {struct st_lsm6dsx_reg reg; TYPE_1__* fs_avl; } ;
struct TYPE_3__ {scalar_t__ gain; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int EINVAL ; 
 int ST_LSM6DSX_FS_LIST_SIZE ; 
 int /*<<< orphan*/  ST_LSM6DSX_SHIFT_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* st_lsm6dsx_fs_table ; 

__attribute__((used)) static int st_lsm6dsx_set_full_scale(struct st_lsm6dsx_sensor *sensor,
				     u32 gain)
{
	struct st_lsm6dsx_hw *hw = sensor->hw;
	const struct st_lsm6dsx_reg *reg;
	int i, err;
	u8 val;

	for (i = 0; i < ST_LSM6DSX_FS_LIST_SIZE; i++)
		if (st_lsm6dsx_fs_table[sensor->id].fs_avl[i].gain == gain)
			break;

	if (i == ST_LSM6DSX_FS_LIST_SIZE)
		return -EINVAL;

	val = st_lsm6dsx_fs_table[sensor->id].fs_avl[i].val;
	reg = &st_lsm6dsx_fs_table[sensor->id].reg;
	err = regmap_update_bits(hw->regmap, reg->addr, reg->mask,
				 ST_LSM6DSX_SHIFT_VAL(val, reg->mask));
	if (err < 0)
		return err;

	sensor->gain = gain;

	return 0;
}