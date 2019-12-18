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
struct rk808_rtc {TYPE_1__* creg; struct rk808* rk808; } ;
struct rk808 {int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  int_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_RTC_INTERRUPTS_REG_IT_ALARM_M ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rk808_rtc_start_alarm(struct rk808_rtc *rk808_rtc)
{
	struct rk808 *rk808 = rk808_rtc->rk808;
	int ret;

	ret = regmap_update_bits(rk808->regmap, rk808_rtc->creg->int_reg,
				 BIT_RTC_INTERRUPTS_REG_IT_ALARM_M,
				 BIT_RTC_INTERRUPTS_REG_IT_ALARM_M);

	return ret;
}