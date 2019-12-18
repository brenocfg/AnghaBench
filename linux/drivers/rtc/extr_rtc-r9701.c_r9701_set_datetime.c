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
struct rtc_time {int tm_year; int tm_hour; int tm_min; int tm_sec; int tm_mday; int tm_mon; int tm_wday; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RDAYCNT ; 
 int /*<<< orphan*/  RHRCNT ; 
 int /*<<< orphan*/  RMINCNT ; 
 int /*<<< orphan*/  RMONCNT ; 
 int /*<<< orphan*/  RSECCNT ; 
 int /*<<< orphan*/  RWKCNT ; 
 int /*<<< orphan*/  RYRCNT ; 
 int bin2bcd (int) ; 
 int write_reg (struct device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int r9701_set_datetime(struct device *dev, struct rtc_time *dt)
{
	int ret, year;

	year = dt->tm_year + 1900;
	if (year >= 2100 || year < 2000)
		return -EINVAL;

	ret = write_reg(dev, RHRCNT, bin2bcd(dt->tm_hour));
	ret = ret ? ret : write_reg(dev, RMINCNT, bin2bcd(dt->tm_min));
	ret = ret ? ret : write_reg(dev, RSECCNT, bin2bcd(dt->tm_sec));
	ret = ret ? ret : write_reg(dev, RDAYCNT, bin2bcd(dt->tm_mday));
	ret = ret ? ret : write_reg(dev, RMONCNT, bin2bcd(dt->tm_mon + 1));
	ret = ret ? ret : write_reg(dev, RYRCNT, bin2bcd(dt->tm_year - 100));
	ret = ret ? ret : write_reg(dev, RWKCNT, 1 << dt->tm_wday);

	return ret;
}