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
struct pm8xxx_rtc_regs {int /*<<< orphan*/  ctrl; } ;
struct pm8xxx_rtc {int /*<<< orphan*/  regmap; struct pm8xxx_rtc_regs* regs; } ;

/* Variables and functions */
 unsigned int PM8xxx_RTC_ENABLE ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int pm8xxx_rtc_enable(struct pm8xxx_rtc *rtc_dd)
{
	const struct pm8xxx_rtc_regs *regs = rtc_dd->regs;
	unsigned int ctrl_reg;
	int rc;

	/* Check if the RTC is on, else turn it on */
	rc = regmap_read(rtc_dd->regmap, regs->ctrl, &ctrl_reg);
	if (rc)
		return rc;

	if (!(ctrl_reg & PM8xxx_RTC_ENABLE)) {
		ctrl_reg |= PM8xxx_RTC_ENABLE;
		rc = regmap_write(rtc_dd->regmap, regs->ctrl, ctrl_reg);
		if (rc)
			return rc;
	}

	return 0;
}