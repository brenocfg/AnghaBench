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
struct rtc_time {int dummy; } ;
struct rtc_wkalrm {int /*<<< orphan*/  enabled; struct rtc_time time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AB8500_RTC ; 
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int /*<<< orphan*/ * ab8500_rtc_alarm_regs ; 
 int ab8500_rtc_irq_enable (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ab8500_rtc_read_time (struct device*,struct rtc_time*) ; 
 int abx500_set_register_interruptible (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  rtc_tm_to_time (struct rtc_time*,unsigned long*) ; 

__attribute__((used)) static int ab8500_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	int retval, i;
	unsigned char buf[ARRAY_SIZE(ab8500_rtc_alarm_regs)];
	unsigned long mins, secs = 0, cursec = 0;
	struct rtc_time curtm;

	/* Get the number of seconds since 1970 */
	rtc_tm_to_time(&alarm->time, &secs);

	/*
	 * Check whether alarm is set less than 1min.
	 * Since our RTC doesn't support alarm resolution less than 1min,
	 * return -EINVAL, so UIE EMUL can take it up, incase of UIE_ON
	 */
	ab8500_rtc_read_time(dev, &curtm); /* Read current time */
	rtc_tm_to_time(&curtm, &cursec);
	if ((secs - cursec) < 59) {
		dev_dbg(dev, "Alarm less than 1 minute not supported\r\n");
		return -EINVAL;
	}

	mins = secs / 60;

	buf[2] = mins & 0xFF;
	buf[1] = (mins >> 8) & 0xFF;
	buf[0] = (mins >> 16) & 0xFF;

	/* Set the alarm time */
	for (i = 0; i < ARRAY_SIZE(ab8500_rtc_alarm_regs); i++) {
		retval = abx500_set_register_interruptible(dev, AB8500_RTC,
			ab8500_rtc_alarm_regs[i], buf[i]);
		if (retval < 0)
			return retval;
	}

	return ab8500_rtc_irq_enable(dev, alarm->enabled);
}