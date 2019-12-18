#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_5__ {int /*<<< orphan*/  mask; scalar_t__ addr; } ;
struct st_lsm6dsx_shub_settings {int dw_slv0_addr; int /*<<< orphan*/  slv0_addr; TYPE_2__ wr_once; } ;
struct TYPE_6__ {int addr; } ;
struct st_lsm6dsx_sensor {TYPE_3__ ext_info; struct st_lsm6dsx_hw* hw; } ;
struct st_lsm6dsx_hw {TYPE_1__* settings; } ;
typedef  int /*<<< orphan*/  config ;
struct TYPE_4__ {struct st_lsm6dsx_shub_settings shub_settings; } ;

/* Variables and functions */
 unsigned int ST_LSM6DSX_SHIFT_VAL (int,int /*<<< orphan*/ ) ; 
 int ST_LSM6DSX_SLV_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int st_lsm6dsx_shub_master_enable (struct st_lsm6dsx_sensor*,int) ; 
 int /*<<< orphan*/  st_lsm6dsx_shub_wait_complete (struct st_lsm6dsx_hw*) ; 
 int st_lsm6dsx_shub_write_reg (struct st_lsm6dsx_hw*,int,int*,int) ; 
 int st_lsm6dsx_shub_write_reg_with_mask (struct st_lsm6dsx_hw*,scalar_t__,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int
st_lsm6dsx_shub_write(struct st_lsm6dsx_sensor *sensor, u8 addr,
		      u8 *data, int len)
{
	const struct st_lsm6dsx_shub_settings *hub_settings;
	struct st_lsm6dsx_hw *hw = sensor->hw;
	u8 config[2], slv_addr;
	int err, i;

	hub_settings = &hw->settings->shub_settings;
	if (hub_settings->wr_once.addr) {
		unsigned int data;

		data = ST_LSM6DSX_SHIFT_VAL(1, hub_settings->wr_once.mask);
		err = st_lsm6dsx_shub_write_reg_with_mask(hw,
			hub_settings->wr_once.addr,
			hub_settings->wr_once.mask,
			data);
		if (err < 0)
			return err;
	}

	slv_addr = ST_LSM6DSX_SLV_ADDR(0, hub_settings->slv0_addr);
	config[0] = sensor->ext_info.addr << 1;
	for (i = 0 ; i < len; i++) {
		config[1] = addr + i;

		err = st_lsm6dsx_shub_write_reg(hw, slv_addr, config,
						sizeof(config));
		if (err < 0)
			return err;

		err = st_lsm6dsx_shub_write_reg(hw, hub_settings->dw_slv0_addr,
						&data[i], 1);
		if (err < 0)
			return err;

		err = st_lsm6dsx_shub_master_enable(sensor, true);
		if (err < 0)
			return err;

		st_lsm6dsx_shub_wait_complete(hw);

		st_lsm6dsx_shub_master_enable(sensor, false);
	}

	memset(config, 0, sizeof(config));
	return st_lsm6dsx_shub_write_reg(hw, slv_addr, config, sizeof(config));
}