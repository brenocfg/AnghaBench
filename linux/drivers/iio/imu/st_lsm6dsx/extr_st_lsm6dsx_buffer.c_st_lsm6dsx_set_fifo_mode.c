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
struct st_lsm6dsx_hw {int fifo_mode; } ;
typedef  enum st_lsm6dsx_fifo_mode { ____Placeholder_st_lsm6dsx_fifo_mode } st_lsm6dsx_fifo_mode ;

/* Variables and functions */
 unsigned int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ST_LSM6DSX_FIFO_MODE_MASK ; 
 int /*<<< orphan*/  ST_LSM6DSX_REG_FIFO_MODE_ADDR ; 
 int st_lsm6dsx_update_bits_locked (struct st_lsm6dsx_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

int st_lsm6dsx_set_fifo_mode(struct st_lsm6dsx_hw *hw,
			     enum st_lsm6dsx_fifo_mode fifo_mode)
{
	unsigned int data;
	int err;

	data = FIELD_PREP(ST_LSM6DSX_FIFO_MODE_MASK, fifo_mode);
	err = st_lsm6dsx_update_bits_locked(hw, ST_LSM6DSX_REG_FIFO_MODE_ADDR,
					    ST_LSM6DSX_FIFO_MODE_MASK, data);
	if (err < 0)
		return err;

	hw->fifo_mode = fifo_mode;

	return 0;
}