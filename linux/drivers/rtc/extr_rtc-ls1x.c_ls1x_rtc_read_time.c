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
typedef  int time64_t ;
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int LS1X_YEAR_MASK ; 
 int /*<<< orphan*/  SYS_TOYREAD0 ; 
 int /*<<< orphan*/  SYS_TOYREAD1 ; 
 int /*<<< orphan*/  ls1x_get_day (unsigned long) ; 
 int /*<<< orphan*/  ls1x_get_hour (unsigned long) ; 
 int /*<<< orphan*/  ls1x_get_min (unsigned long) ; 
 int /*<<< orphan*/  ls1x_get_month (unsigned long) ; 
 int /*<<< orphan*/  ls1x_get_sec (unsigned long) ; 
 int /*<<< orphan*/  memset (struct rtc_time*,int /*<<< orphan*/ ,int) ; 
 int mktime64 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (int,struct rtc_time*) ; 

__attribute__((used)) static int ls1x_rtc_read_time(struct device *dev, struct rtc_time *rtm)
{
	unsigned long v;
	time64_t t;

	v = readl(SYS_TOYREAD0);
	t = readl(SYS_TOYREAD1);

	memset(rtm, 0, sizeof(struct rtc_time));
	t  = mktime64((t & LS1X_YEAR_MASK), ls1x_get_month(v),
			ls1x_get_day(v), ls1x_get_hour(v),
			ls1x_get_min(v), ls1x_get_sec(v));
	rtc_time64_to_tm(t, rtm);

	return 0;
}