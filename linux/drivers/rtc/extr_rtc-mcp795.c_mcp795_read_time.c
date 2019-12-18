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
struct rtc_time {void* tm_year; void* tm_mon; void* tm_mday; void* tm_wday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  MCP795_REG_SECONDS ; 
 void* bcd2bin (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,struct rtc_time*) ; 
 int mcp795_rtcc_read (struct device*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int mcp795_read_time(struct device *dev, struct rtc_time *tim)
{
	int ret;
	u8 data[7];

	ret = mcp795_rtcc_read(dev, MCP795_REG_SECONDS, data, sizeof(data));

	if (ret)
		return ret;

	tim->tm_sec	= bcd2bin(data[0] & 0x7F);
	tim->tm_min	= bcd2bin(data[1] & 0x7F);
	tim->tm_hour	= bcd2bin(data[2] & 0x3F);
	tim->tm_wday	= bcd2bin(data[3] & 0x07) - 1;
	tim->tm_mday	= bcd2bin(data[4] & 0x3F);
	tim->tm_mon	= bcd2bin(data[5] & 0x1F) - 1;
	tim->tm_year	= bcd2bin(data[6]) + 100; /* Assume we are in 20xx */

	dev_dbg(dev, "Read from mcp795: %ptR\n", tim);

	return 0;
}