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
typedef  int u8 ;
typedef  int u32 ;
struct timespec64 {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_DAY_OF_MONTH ; 
 int /*<<< orphan*/  RTC_FREQ_SELECT ; 
 int /*<<< orphan*/  RTC_HOURS ; 
 int /*<<< orphan*/  RTC_MINUTES ; 
 int /*<<< orphan*/  RTC_MONTH ; 
 int /*<<< orphan*/  RTC_SECONDS ; 
 int RTC_UIP ; 
 int /*<<< orphan*/  RTC_YEAR ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  mktime64 (int,int,int,int,int,int) ; 
 int /*<<< orphan*/  pr_info (char*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int vrtc_cmos_read (int /*<<< orphan*/ ) ; 

void vrtc_get_time(struct timespec64 *now)
{
	u8 sec, min, hour, mday, mon;
	unsigned long flags;
	u32 year;

	spin_lock_irqsave(&rtc_lock, flags);

	while ((vrtc_cmos_read(RTC_FREQ_SELECT) & RTC_UIP))
		cpu_relax();

	sec = vrtc_cmos_read(RTC_SECONDS);
	min = vrtc_cmos_read(RTC_MINUTES);
	hour = vrtc_cmos_read(RTC_HOURS);
	mday = vrtc_cmos_read(RTC_DAY_OF_MONTH);
	mon = vrtc_cmos_read(RTC_MONTH);
	year = vrtc_cmos_read(RTC_YEAR);

	spin_unlock_irqrestore(&rtc_lock, flags);

	/* vRTC YEAR reg contains the offset to 1972 */
	year += 1972;

	pr_info("vRTC: sec: %d min: %d hour: %d day: %d "
		"mon: %d year: %d\n", sec, min, hour, mday, mon, year);

	now->tv_sec = mktime64(year, mon, mday, hour, min, sec);
	now->tv_nsec = 0;
}