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
struct stmp3xxx_rtc_data {scalar_t__ io; } ;

/* Variables and functions */
 int ETIME ; 
 scalar_t__ STMP3XXX_RTC_STAT ; 
 int STMP3XXX_RTC_STAT_STALE_SHIFT ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int stmp3xxx_wait_time(struct stmp3xxx_rtc_data *rtc_data)
{
	int timeout = 5000; /* 3ms according to i.MX28 Ref Manual */
	/*
	 * The i.MX28 Applications Processor Reference Manual, Rev. 1, 2010
	 * states:
	 * | The order in which registers are updated is
	 * | Persistent 0, 1, 2, 3, 4, 5, Alarm, Seconds.
	 * | (This list is in bitfield order, from LSB to MSB, as they would
	 * | appear in the STALE_REGS and NEW_REGS bitfields of the HW_RTC_STAT
	 * | register. For example, the Seconds register corresponds to
	 * | STALE_REGS or NEW_REGS containing 0x80.)
	 */
	do {
		if (!(readl(rtc_data->io + STMP3XXX_RTC_STAT) &
				(0x80 << STMP3XXX_RTC_STAT_STALE_SHIFT)))
			return 0;
		udelay(1);
	} while (--timeout > 0);
	return (readl(rtc_data->io + STMP3XXX_RTC_STAT) &
		(0x80 << STMP3XXX_RTC_STAT_STALE_SHIFT)) ? -ETIME : 0;
}