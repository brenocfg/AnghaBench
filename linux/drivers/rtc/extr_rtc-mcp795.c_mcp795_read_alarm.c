#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {int tm_year; int tm_isdst; int tm_yday; void* tm_wday; void* tm_mon; void* tm_mday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct rtc_wkalrm {TYPE_1__ time; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  MCP795_REG_ALM0_SECONDS ; 
 void* bcd2bin (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,TYPE_1__*,void*,TYPE_1__*) ; 
 int mcp795_rtcc_read (struct device*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int mcp795_read_alarm(struct device *dev, struct rtc_wkalrm *alm)
{
	u8 data[6];
	int ret;

	ret = mcp795_rtcc_read(
			dev, MCP795_REG_ALM0_SECONDS, data, sizeof(data));
	if (ret)
		return ret;

	alm->time.tm_sec	= bcd2bin(data[0] & 0x7F);
	alm->time.tm_min	= bcd2bin(data[1] & 0x7F);
	alm->time.tm_hour	= bcd2bin(data[2] & 0x1F);
	alm->time.tm_wday	= bcd2bin(data[3] & 0x07) - 1;
	alm->time.tm_mday	= bcd2bin(data[4] & 0x3F);
	alm->time.tm_mon	= bcd2bin(data[5] & 0x1F) - 1;
	alm->time.tm_year	= -1;
	alm->time.tm_isdst	= -1;
	alm->time.tm_yday	= -1;

	dev_dbg(dev, "Read alarm: %ptRdr(%d) %ptRt\n",
		&alm->time, alm->time.tm_wday, &alm->time);
	return 0;
}