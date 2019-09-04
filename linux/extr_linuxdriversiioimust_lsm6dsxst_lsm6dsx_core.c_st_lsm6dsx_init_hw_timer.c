#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  mask; scalar_t__ addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  mask; scalar_t__ addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  mask; scalar_t__ addr; } ;
struct st_lsm6dsx_hw_ts_settings {TYPE_4__ fifo_en; TYPE_3__ hr_timer; TYPE_2__ timer_en; } ;
struct st_lsm6dsx_hw {int /*<<< orphan*/  regmap; TYPE_1__* settings; } ;
struct TYPE_5__ {struct st_lsm6dsx_hw_ts_settings ts_settings; } ;

/* Variables and functions */
 int ST_LSM6DSX_SHIFT_VAL (int,int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int st_lsm6dsx_init_hw_timer(struct st_lsm6dsx_hw *hw)
{
	const struct st_lsm6dsx_hw_ts_settings *ts_settings;
	int err, val;

	ts_settings = &hw->settings->ts_settings;
	/* enable hw timestamp generation if necessary */
	if (ts_settings->timer_en.addr) {
		val = ST_LSM6DSX_SHIFT_VAL(1, ts_settings->timer_en.mask);
		err = regmap_update_bits(hw->regmap,
					 ts_settings->timer_en.addr,
					 ts_settings->timer_en.mask, val);
		if (err < 0)
			return err;
	}

	/* enable high resolution for hw ts timer if necessary */
	if (ts_settings->hr_timer.addr) {
		val = ST_LSM6DSX_SHIFT_VAL(1, ts_settings->hr_timer.mask);
		err = regmap_update_bits(hw->regmap,
					 ts_settings->hr_timer.addr,
					 ts_settings->hr_timer.mask, val);
		if (err < 0)
			return err;
	}

	/* enable ts queueing in FIFO if necessary */
	if (ts_settings->fifo_en.addr) {
		val = ST_LSM6DSX_SHIFT_VAL(1, ts_settings->fifo_en.mask);
		err = regmap_update_bits(hw->regmap,
					 ts_settings->fifo_en.addr,
					 ts_settings->fifo_en.mask, val);
		if (err < 0)
			return err;
	}
	return 0;
}