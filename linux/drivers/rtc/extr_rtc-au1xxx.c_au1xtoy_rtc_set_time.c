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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AU1000_SYS_CNTRCTRL ; 
 int /*<<< orphan*/  AU1000_SYS_TOYWRITE ; 
 int SYS_CNTRL_C0S ; 
 int alchemy_rdsys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alchemy_wrsys (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rtc_tm_to_time (struct rtc_time*,unsigned long*) ; 

__attribute__((used)) static int au1xtoy_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	unsigned long t;

	rtc_tm_to_time(tm, &t);

	alchemy_wrsys(t, AU1000_SYS_TOYWRITE);

	/* wait for the pending register write to succeed.  This can
	 * take up to 6 seconds...
	 */
	while (alchemy_rdsys(AU1000_SYS_CNTRCTRL) & SYS_CNTRL_C0S)
		msleep(1);

	return 0;
}