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
struct rohm_regmap_dev {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int BD70528_ELAPSED_STATE_BIT ; 
 unsigned int BD70528_MASK_ELAPSED_TIMER_EN ; 
 int /*<<< orphan*/  BD70528_REG_ELAPSED_TIMER_EN ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int bd70528_set_elapsed_tmr(struct rohm_regmap_dev *bd70528,
				   int enable, int *old_state)
{
	int ret;
	unsigned int ctrl_reg;

	/*
	 * TBD
	 * What is the purpose of elapsed timer ?
	 * Is the timeout registers counting down, or is the disable - re-enable
	 * going to restart the elapsed-time counting? If counting is restarted
	 * the timeout should be decreased by the amount of time that has
	 * elapsed since starting the timer. Maybe we should store the monotonic
	 * clock value when timer is started so that if RTC is set while timer
	 * is armed we could do the compensation. This is a hack if RTC/system
	 * clk are drifting. OTOH, RTC controlled via I2C is in any case
	 * inaccurate...
	 */
	ret = regmap_read(bd70528->regmap, BD70528_REG_ELAPSED_TIMER_EN,
			  &ctrl_reg);
	if (ret)
		return ret;

	if (old_state) {
		if (ctrl_reg & BD70528_MASK_ELAPSED_TIMER_EN)
			*old_state |= BD70528_ELAPSED_STATE_BIT;
		else
			*old_state &= ~BD70528_ELAPSED_STATE_BIT;

		if ((!enable) == (!(*old_state & BD70528_ELAPSED_STATE_BIT)))
			return 0;
	}

	if (enable)
		ctrl_reg |= BD70528_MASK_ELAPSED_TIMER_EN;
	else
		ctrl_reg &= ~BD70528_MASK_ELAPSED_TIMER_EN;

	return regmap_write(bd70528->regmap, BD70528_REG_ELAPSED_TIMER_EN,
			    ctrl_reg);
}