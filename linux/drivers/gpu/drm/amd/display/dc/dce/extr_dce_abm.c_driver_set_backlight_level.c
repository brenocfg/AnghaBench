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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct dce_abm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BL_ACTIVE_INT_FRAC_CNT ; 
 int /*<<< orphan*/  BL_PWM_CNTL ; 
 int /*<<< orphan*/  BL_PWM_GRP1_IGNORE_MASTER_LOCK_EN ; 
 int /*<<< orphan*/  BL_PWM_GRP1_REG_LOCK ; 
 int /*<<< orphan*/  BL_PWM_GRP1_REG_UPDATE_PENDING ; 
 int /*<<< orphan*/  BL_PWM_PERIOD ; 
 int /*<<< orphan*/  BL_PWM_PERIOD_BITCNT ; 
 int /*<<< orphan*/  BL_PWM_PERIOD_CNTL ; 
 int /*<<< orphan*/  REG_GET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WAIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void driver_set_backlight_level(struct dce_abm *abm_dce,
		uint32_t backlight_pwm_u16_16)
{
	uint32_t backlight_16bit;
	uint32_t masked_pwm_period;
	uint8_t bit_count;
	uint64_t active_duty_cycle;
	uint32_t pwm_period_bitcnt;

	/*
	 * 1. Find  16 bit backlight active duty cycle, where 0 <= backlight
	 * active duty cycle <= backlight period
	 */

	/* 1.1 Apply bitmask for backlight period value based on value of BITCNT
	 */
	REG_GET_2(BL_PWM_PERIOD_CNTL,
			BL_PWM_PERIOD_BITCNT, &pwm_period_bitcnt,
			BL_PWM_PERIOD, &masked_pwm_period);

	if (pwm_period_bitcnt == 0)
		bit_count = 16;
	else
		bit_count = pwm_period_bitcnt;

	/* e.g. maskedPwmPeriod = 0x24 when bitCount is 6 */
	masked_pwm_period = masked_pwm_period & ((1 << bit_count) - 1);

	/* 1.2 Calculate integer active duty cycle required upper 16 bits
	 * contain integer component, lower 16 bits contain fractional component
	 * of active duty cycle e.g. 0x21BDC0 = 0xEFF0 * 0x24
	 */
	active_duty_cycle = backlight_pwm_u16_16 * masked_pwm_period;

	/* 1.3 Calculate 16 bit active duty cycle from integer and fractional
	 * components shift by bitCount then mask 16 bits and add rounding bit
	 * from MSB of fraction e.g. 0x86F7 = ((0x21BDC0 >> 6) & 0xFFF) + 0
	 */
	backlight_16bit = active_duty_cycle >> bit_count;
	backlight_16bit &= 0xFFFF;
	backlight_16bit += (active_duty_cycle >> (bit_count - 1)) & 0x1;

	/*
	 * 2. Program register with updated value
	 */

	/* 2.1 Lock group 2 backlight registers */

	REG_UPDATE_2(BL_PWM_GRP1_REG_LOCK,
			BL_PWM_GRP1_IGNORE_MASTER_LOCK_EN, 1,
			BL_PWM_GRP1_REG_LOCK, 1);

	// 2.2 Write new active duty cycle
	REG_UPDATE(BL_PWM_CNTL, BL_ACTIVE_INT_FRAC_CNT, backlight_16bit);

	/* 2.3 Unlock group 2 backlight registers */
	REG_UPDATE(BL_PWM_GRP1_REG_LOCK,
			BL_PWM_GRP1_REG_LOCK, 0);

	/* 3 Wait for pending bit to be cleared */
	REG_WAIT(BL_PWM_GRP1_REG_LOCK,
			BL_PWM_GRP1_REG_UPDATE_PENDING, 0,
			1, 10000);
}