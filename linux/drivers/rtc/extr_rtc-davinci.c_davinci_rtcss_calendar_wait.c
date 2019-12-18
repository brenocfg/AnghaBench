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
struct davinci_rtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRTCSS_RTC_CCTRL ; 
 int PRTCSS_RTC_CCTRL_CALBUSY ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int rtcss_read (struct davinci_rtc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void davinci_rtcss_calendar_wait(struct davinci_rtc *davinci_rtc)
{
	while (rtcss_read(davinci_rtc, PRTCSS_RTC_CCTRL) &
	       PRTCSS_RTC_CCTRL_CALBUSY)
		cpu_relax();
}