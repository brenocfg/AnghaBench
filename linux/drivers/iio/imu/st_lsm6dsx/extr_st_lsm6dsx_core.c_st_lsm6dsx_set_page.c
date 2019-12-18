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
struct TYPE_4__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;
struct st_lsm6dsx_shub_settings {TYPE_2__ page_mux; } ;
struct st_lsm6dsx_hw {int /*<<< orphan*/  regmap; TYPE_1__* settings; } ;
struct TYPE_3__ {struct st_lsm6dsx_shub_settings shub_settings; } ;

/* Variables and functions */
 unsigned int ST_LSM6DSX_SHIFT_VAL (int,int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int st_lsm6dsx_set_page(struct st_lsm6dsx_hw *hw, bool enable)
{
	const struct st_lsm6dsx_shub_settings *hub_settings;
	unsigned int data;
	int err;

	hub_settings = &hw->settings->shub_settings;
	data = ST_LSM6DSX_SHIFT_VAL(enable, hub_settings->page_mux.mask);
	err = regmap_update_bits(hw->regmap, hub_settings->page_mux.addr,
				 hub_settings->page_mux.mask, data);
	usleep_range(100, 150);

	return err;
}