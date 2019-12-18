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
struct st_lsm6dsx_hw {int /*<<< orphan*/  regmap; TYPE_1__* settings; } ;
struct TYPE_2__ {int /*<<< orphan*/  reset_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ST_LSM6DSX_REG_BDU_ADDR ; 
 int /*<<< orphan*/  ST_LSM6DSX_REG_BDU_MASK ; 
 int /*<<< orphan*/  ST_LSM6DSX_REG_BOOT_MASK ; 
 int /*<<< orphan*/  ST_LSM6DSX_REG_FIFO_FTH_IRQ_MASK ; 
 int /*<<< orphan*/  ST_LSM6DSX_REG_RESET_MASK ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int st_lsm6dsx_get_drdy_reg (struct st_lsm6dsx_hw*,int /*<<< orphan*/ *) ; 
 int st_lsm6dsx_init_hw_timer (struct st_lsm6dsx_hw*) ; 
 int st_lsm6dsx_init_shub (struct st_lsm6dsx_hw*) ; 

__attribute__((used)) static int st_lsm6dsx_init_device(struct st_lsm6dsx_hw *hw)
{
	u8 drdy_int_reg;
	int err;

	/* device sw reset */
	err = regmap_update_bits(hw->regmap, hw->settings->reset_addr,
				 ST_LSM6DSX_REG_RESET_MASK,
				 FIELD_PREP(ST_LSM6DSX_REG_RESET_MASK, 1));
	if (err < 0)
		return err;

	msleep(50);

	/* reload trimming parameter */
	err = regmap_update_bits(hw->regmap, hw->settings->reset_addr,
				 ST_LSM6DSX_REG_BOOT_MASK,
				 FIELD_PREP(ST_LSM6DSX_REG_BOOT_MASK, 1));
	if (err < 0)
		return err;

	msleep(50);

	/* enable Block Data Update */
	err = regmap_update_bits(hw->regmap, ST_LSM6DSX_REG_BDU_ADDR,
				 ST_LSM6DSX_REG_BDU_MASK,
				 FIELD_PREP(ST_LSM6DSX_REG_BDU_MASK, 1));
	if (err < 0)
		return err;

	/* enable FIFO watermak interrupt */
	err = st_lsm6dsx_get_drdy_reg(hw, &drdy_int_reg);
	if (err < 0)
		return err;

	err = regmap_update_bits(hw->regmap, drdy_int_reg,
				 ST_LSM6DSX_REG_FIFO_FTH_IRQ_MASK,
				 FIELD_PREP(ST_LSM6DSX_REG_FIFO_FTH_IRQ_MASK,
					    1));
	if (err < 0)
		return err;

	err = st_lsm6dsx_init_shub(hw);
	if (err < 0)
		return err;

	return st_lsm6dsx_init_hw_timer(hw);
}