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
struct TYPE_2__ {unsigned char tm_hour; unsigned char tm_min; unsigned char tm_sec; } ;
struct rtc_wkalrm {scalar_t__ enabled; TYPE_1__ time; } ;
struct mrst_rtc {int /*<<< orphan*/  irq; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IPCMSG_VRTC ; 
 int /*<<< orphan*/  IPC_CMD_VRTC_SETALARM ; 
 int /*<<< orphan*/  RTC_AIE ; 
 int /*<<< orphan*/  RTC_HOURS_ALARM ; 
 int /*<<< orphan*/  RTC_MINUTES_ALARM ; 
 int /*<<< orphan*/  RTC_SECONDS_ALARM ; 
 struct mrst_rtc* dev_get_drvdata (struct device*) ; 
 int intel_scu_ipc_simple_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrst_irq_disable (struct mrst_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrst_irq_enable (struct mrst_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vrtc_cmos_write (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mrst_set_alarm(struct device *dev, struct rtc_wkalrm *t)
{
	struct mrst_rtc	*mrst = dev_get_drvdata(dev);
	unsigned char hrs, min, sec;
	int ret = 0;

	if (!mrst->irq)
		return -EIO;

	hrs = t->time.tm_hour;
	min = t->time.tm_min;
	sec = t->time.tm_sec;

	spin_lock_irq(&rtc_lock);
	/* Next rtc irq must not be from previous alarm setting */
	mrst_irq_disable(mrst, RTC_AIE);

	/* Update alarm */
	vrtc_cmos_write(hrs, RTC_HOURS_ALARM);
	vrtc_cmos_write(min, RTC_MINUTES_ALARM);
	vrtc_cmos_write(sec, RTC_SECONDS_ALARM);

	spin_unlock_irq(&rtc_lock);

	ret = intel_scu_ipc_simple_command(IPCMSG_VRTC, IPC_CMD_VRTC_SETALARM);
	if (ret)
		return ret;

	spin_lock_irq(&rtc_lock);
	if (t->enabled)
		mrst_irq_enable(mrst, RTC_AIE);

	spin_unlock_irq(&rtc_lock);

	return 0;
}