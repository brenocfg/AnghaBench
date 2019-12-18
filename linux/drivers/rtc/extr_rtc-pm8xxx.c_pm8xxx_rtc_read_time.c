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
typedef  int /*<<< orphan*/  value ;
typedef  unsigned int u8 ;
struct rtc_time {int dummy; } ;
struct pm8xxx_rtc_regs {int /*<<< orphan*/  read; } ;
struct pm8xxx_rtc {int /*<<< orphan*/  regmap; struct pm8xxx_rtc_regs* regs; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int NUM_8_BIT_RTC_REGS ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned long,struct rtc_time*,struct rtc_time*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct pm8xxx_rtc* dev_get_drvdata (struct device*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  rtc_time_to_tm (unsigned long,struct rtc_time*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int pm8xxx_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	int rc;
	u8 value[NUM_8_BIT_RTC_REGS];
	unsigned long secs;
	unsigned int reg;
	struct pm8xxx_rtc *rtc_dd = dev_get_drvdata(dev);
	const struct pm8xxx_rtc_regs *regs = rtc_dd->regs;

	rc = regmap_bulk_read(rtc_dd->regmap, regs->read, value, sizeof(value));
	if (rc) {
		dev_err(dev, "RTC read data register failed\n");
		return rc;
	}

	/*
	 * Read the LSB again and check if there has been a carry over.
	 * If there is, redo the read operation.
	 */
	rc = regmap_read(rtc_dd->regmap, regs->read, &reg);
	if (rc < 0) {
		dev_err(dev, "RTC read data register failed\n");
		return rc;
	}

	if (unlikely(reg < value[0])) {
		rc = regmap_bulk_read(rtc_dd->regmap, regs->read,
				      value, sizeof(value));
		if (rc) {
			dev_err(dev, "RTC read data register failed\n");
			return rc;
		}
	}

	secs = value[0] | (value[1] << 8) | (value[2] << 16) |
	       ((unsigned long)value[3] << 24);

	rtc_time_to_tm(secs, tm);

	dev_dbg(dev, "secs = %lu, h:m:s == %ptRt, y-m-d = %ptRdr\n", secs, tm, tm);

	return 0;
}