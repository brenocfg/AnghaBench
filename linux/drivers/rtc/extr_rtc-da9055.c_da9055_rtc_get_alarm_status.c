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
struct da9055 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9055_REG_ALARM_Y ; 
 int DA9055_RTC_ALM_EN ; 
 int da9055_reg_read (struct da9055*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int da9055_rtc_get_alarm_status(struct da9055 *da9055)
{
	int ret;

	ret = da9055_reg_read(da9055, DA9055_REG_ALARM_Y);
	if (ret < 0) {
		dev_err(da9055->dev, "Failed to read ALM: %d\n", ret);
		return ret;
	}
	ret &= DA9055_RTC_ALM_EN;
	return (ret > 0) ? 1 : 0;
}