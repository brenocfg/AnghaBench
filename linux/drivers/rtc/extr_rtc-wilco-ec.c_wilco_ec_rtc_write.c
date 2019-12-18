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
struct wilco_ec_message {int request_size; struct ec_rtc_write_request* request_data; int /*<<< orphan*/  type; } ;
struct wilco_ec_device {int dummy; } ;
struct rtc_time {int tm_year; int tm_wday; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; } ;
struct ec_rtc_write_request {void* weekday; void* second; void* minute; void* hour; void* day; void* month; void* year; void* century; int /*<<< orphan*/  param; int /*<<< orphan*/  command; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  rtc ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  EC_CMOS_TOD_WRITE ; 
 int /*<<< orphan*/  EC_COMMAND_CMOS ; 
 int /*<<< orphan*/  WILCO_EC_MSG_LEGACY ; 
 void* bin2bcd (int) ; 
 struct wilco_ec_device* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct wilco_ec_message*,int /*<<< orphan*/ ,int) ; 
 int wilco_ec_mailbox (struct wilco_ec_device*,struct wilco_ec_message*) ; 

__attribute__((used)) static int wilco_ec_rtc_write(struct device *dev, struct rtc_time *tm)
{
	struct wilco_ec_device *ec = dev_get_drvdata(dev->parent);
	struct ec_rtc_write_request rtc;
	struct wilco_ec_message msg;
	int year = tm->tm_year + 1900;
	/*
	 * Convert from 0=Sunday to 0=Saturday for the EC
	 * We DO need to set weekday because the EC controls battery charging
	 * schedules that depend on the day of the week.
	 */
	int wday = tm->tm_wday == 6 ? 0 : tm->tm_wday + 1;
	int ret;

	rtc.command	= EC_COMMAND_CMOS;
	rtc.param	= EC_CMOS_TOD_WRITE;
	rtc.century	= bin2bcd(year / 100);
	rtc.year	= bin2bcd(year % 100);
	rtc.month	= bin2bcd(tm->tm_mon + 1);
	rtc.day		= bin2bcd(tm->tm_mday);
	rtc.hour	= bin2bcd(tm->tm_hour);
	rtc.minute	= bin2bcd(tm->tm_min);
	rtc.second	= bin2bcd(tm->tm_sec);
	rtc.weekday	= bin2bcd(wday);

	memset(&msg, 0, sizeof(msg));
	msg.type = WILCO_EC_MSG_LEGACY;
	msg.request_data = &rtc;
	msg.request_size = sizeof(rtc);

	ret = wilco_ec_mailbox(ec, &msg);
	if (ret < 0)
		return ret;

	return 0;
}