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
struct st_lsm6dsx_shub_settings {int /*<<< orphan*/  shub_out; int /*<<< orphan*/  slv0_addr; } ;
struct TYPE_4__ {int addr; } ;
struct st_lsm6dsx_sensor {TYPE_2__ ext_info; struct st_lsm6dsx_hw* hw; } ;
struct st_lsm6dsx_hw {TYPE_1__* settings; } ;
typedef  int /*<<< orphan*/  config ;
struct TYPE_3__ {struct st_lsm6dsx_shub_settings shub_settings; } ;

/* Variables and functions */
 int ST_LS6DSX_READ_OP_MASK ; 
 int ST_LSM6DSX_SLV_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int st_lsm6dsx_shub_master_enable (struct st_lsm6dsx_sensor*,int) ; 
 int st_lsm6dsx_shub_read_reg (struct st_lsm6dsx_hw*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  st_lsm6dsx_shub_wait_complete (struct st_lsm6dsx_hw*) ; 
 int st_lsm6dsx_shub_write_reg (struct st_lsm6dsx_hw*,int,int*,int) ; 

__attribute__((used)) static int
st_lsm6dsx_shub_read(struct st_lsm6dsx_sensor *sensor, u8 addr,
		     u8 *data, int len)
{
	const struct st_lsm6dsx_shub_settings *hub_settings;
	struct st_lsm6dsx_hw *hw = sensor->hw;
	u8 config[3], slv_addr;
	int err;

	hub_settings = &hw->settings->shub_settings;
	slv_addr = ST_LSM6DSX_SLV_ADDR(0, hub_settings->slv0_addr);

	config[0] = (sensor->ext_info.addr << 1) | 1;
	config[1] = addr;
	config[2] = len & ST_LS6DSX_READ_OP_MASK;

	err = st_lsm6dsx_shub_write_reg(hw, slv_addr, config,
					sizeof(config));
	if (err < 0)
		return err;

	err = st_lsm6dsx_shub_master_enable(sensor, true);
	if (err < 0)
		return err;

	st_lsm6dsx_shub_wait_complete(hw);

	err = st_lsm6dsx_shub_read_reg(hw, hub_settings->shub_out, data,
				       len & ST_LS6DSX_READ_OP_MASK);

	st_lsm6dsx_shub_master_enable(sensor, false);

	memset(config, 0, sizeof(config));
	return st_lsm6dsx_shub_write_reg(hw, slv_addr, config,
					 sizeof(config));
}