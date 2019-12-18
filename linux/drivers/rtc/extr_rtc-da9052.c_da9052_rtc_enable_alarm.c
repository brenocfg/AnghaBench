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
struct da9052_rtc {int /*<<< orphan*/  da9052; } ;

/* Variables and functions */
 int DA9052_ALARM_Y_ALARM_ON ; 
 int /*<<< orphan*/  DA9052_ALARM_Y_REG ; 
 int DA9052_ALARM_Y_TICK_ON ; 
 int da9052_reg_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtc_err (struct da9052_rtc*,char*,int) ; 

__attribute__((used)) static int da9052_rtc_enable_alarm(struct da9052_rtc *rtc, bool enable)
{
	int ret;
	if (enable) {
		ret = da9052_reg_update(rtc->da9052, DA9052_ALARM_Y_REG,
				DA9052_ALARM_Y_ALARM_ON|DA9052_ALARM_Y_TICK_ON,
				DA9052_ALARM_Y_ALARM_ON);
		if (ret != 0)
			rtc_err(rtc, "Failed to enable ALM: %d\n", ret);
	} else {
		ret = da9052_reg_update(rtc->da9052, DA9052_ALARM_Y_REG,
			DA9052_ALARM_Y_ALARM_ON|DA9052_ALARM_Y_TICK_ON, 0);
		if (ret != 0)
			rtc_err(rtc, "Write error: %d\n", ret);
	}
	return ret;
}